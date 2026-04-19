/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:22:43 by razaccar          #+#    #+#             */
/*   Updated: 2026/04/16 05:01:53 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// #include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct client {
    int     id;
    char    *recv_buf;
    char    *send_buf;
} client_t;

void panic(char *err)
{
    write(STDERR_FILENO, err, strlen(err));
    exit(1); 
}

void print_address(uint32_t ip, uint16_t port)
{
    uint8_t ip_parts[4];
    ip_parts[0] = ip >> 24;
    ip_parts[1] = ip >> 16;
    ip_parts[2] = ip >> 8;
    ip_parts[3] = ip >> 0;
    printf("IP:   %d.%d.%d.%d\n", ip_parts[3], ip_parts[2], ip_parts[1], ip_parts[0]);
    printf("PORT: %d\n", ntohs(port));
}

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i]) {
		if ((*buf)[i] == '\n') {
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

void broadcast(client_t *clients, char *msg, int maxfd)
{
    for (int fd = 0; fd <= maxfd; ++fd) {
        if (clients[fd].id != 0) {
            if (clients[fd].send_buf) {
                char *temp = malloc(strlen(clients[fd].send_buf) + strlen(msg) + 1);
                strcpy(temp, clients[fd].send_buf);
                strcat(temp, msg);
                free(clients[fd].send_buf);
                clients[fd].send_buf = temp;
            }
            else {
                clients[fd].send_buf = malloc(strlen(msg) + 1);
                strcpy(clients[fd].send_buf, msg);
            }
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2) panic("Wrong number of arguments\n");
    uint16_t arg = atoi(av[1]);

    uint32_t ip = (1 << 24) | (0 << 16) | (0 << 8) | 127;
    uint16_t port = ((arg >> 8) & 0x00FF) | ((arg << 8) & 0xFF00);
    struct sockaddr_in server = {.sin_family = AF_INET, .sin_addr.s_addr = ip, .sin_port = port};

    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == -1)
        panic("Fatal error (socket)\n");
    if ((bind(listen_sock, (const struct sockaddr*)&server, sizeof(struct sockaddr))) != 0)
        panic("Fatal error (bind)\n");
	if (listen(listen_sock, 10) != 0)
        panic("Fatal error (listen)\n");

    client_t clients[FD_SETSIZE] = {0};
    int n_client = 1;
    int maxfd = listen_sock; 
    fd_set active, rset, wset;
    FD_ZERO(&active);
    FD_SET(listen_sock, &active);

    while (1) {
        FD_ZERO(&wset);
        FD_ZERO(&rset);
        rset = active;
        
        for (int fd = 0; fd <= maxfd; ++fd) {
            if (FD_ISSET(fd, &active) && fd != listen_sock && clients[fd].send_buf)
                FD_SET(fd, &wset);
        }
        
        if (select(maxfd + 1, &rset, &wset, NULL, NULL) < 0)
            panic("Fatal error (select)\n");

        for (int fd = 0; fd <= maxfd; ++fd) {
            if (FD_ISSET(fd, &rset)) {
                if (fd == listen_sock) {
                    int newfd = accept(listen_sock, NULL, NULL);
                    if (newfd == -1) panic("Fatal error\n");
                    FD_SET(newfd, &active);
                    clients[newfd].id = n_client++;
                    maxfd = newfd > maxfd ? newfd : maxfd;
                    char *fmt = "server: client %d just arrived\n";
                    char msg[(strlen(fmt) - 2) + FD_SETSIZE + 1];
                    sprintf(msg, fmt, clients[newfd].id - 1);
                    broadcast(clients, msg, maxfd);
                }
                else {
                    client_t *c = &(clients[fd]);
                    char buf[11];
                    char *bytes;
                    ssize_t read_bytes = recv(fd, buf, 10, 0);
                    if (!read_bytes) {
                        char *fmt = "server: client %d just left\n";
                        char msg[(strlen(fmt) - 2) + FD_SETSIZE + 1];
                        sprintf(msg, fmt, c->id + 1);
                        FD_CLR(fd, &active);
                        clients[fd].id = 0;
                        if (clients[fd].recv_buf) free(clients[fd].recv_buf);
                        if (clients[fd].send_buf) free(clients[fd].send_buf);
                        clients[fd].send_buf = NULL;
                        close(fd);
                        broadcast(clients, msg, maxfd);
                    }
                    else {
                        if (!c->recv_buf) c->recv_buf = calloc(11, sizeof(char));
                        else c->recv_buf = realloc(c->recv_buf, strlen(c->recv_buf) + 11);
                        buf[read_bytes] = 0;
                        strcat(c->recv_buf, buf);
                        int message = extract_message(&c->recv_buf, &bytes);
                        if (message) {
                            while (message) {
                                char *fmt = "client %d: %s";
                                char msg[(strlen(fmt) - 4) + strlen(bytes) + FD_SETSIZE + 1];
                                sprintf(msg, fmt, c->id - 1, bytes);
                                broadcast(clients, msg, maxfd);
                                free(bytes);
                                message = extract_message(&c->recv_buf, &bytes);
                            }
                            free(c->recv_buf);
                            c->recv_buf = NULL;
                        }
                    }
                }
            }
        }
		for (int fd = 0; fd <= maxfd; fd++) {
            if (FD_ISSET(fd, &wset) && fd != listen_sock) {
                if (!clients[fd].send_buf) continue;
                if (send(fd, clients[fd].send_buf, strlen(clients[fd].send_buf), 0) > 0) {
                    free(clients[fd].send_buf);
                    clients[fd].send_buf = NULL;
                }
            }
        }
    }
}
