/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:22:43 by razaccar          #+#    #+#             */
/*   Updated: 2026/04/23 17:44:04 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
// #include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct client {
    int     id;
    int     fd; 
    char    *rbuf;
    char    *wbuf;
} client_t;

int         sock;
client_t    clients[4096];
int         n_clients;
int         max_sock;
fd_set      active, rset, wset;

void panic(char *err)
{
    write(STDERR_FILENO, err, strlen(err));
    exit(1); 
}

int extract_line(char **buf, char **msg)
{
	char	*newbuf;
	int	    i;

	*msg = NULL;
	i = 0;
	if (!*buf) return (0);
	while ((*buf)[i]) {
		if ((*buf)[i] == '\n') {
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (!newbuf) return (-1);
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

void broadcast(client_t *clients, char *msg)
{
    for (int i = 0; i < n_clients; ++i) {
        if (clients[i].id < 0) continue;
        if (clients[i].wbuf) {
            clients[i].wbuf = realloc(clients[i].wbuf, strlen(clients[i].wbuf) + strlen(msg) + 1);
            strcat(clients[i].wbuf, msg);
        }
        else {
            clients[i].wbuf = malloc(strlen(msg) + 1);
            strcpy(clients[i].wbuf, msg);
        }
    }
}

void add_client(int c_sock)
{
    FD_SET(c_sock, &active);
    clients[n_clients].id = n_clients;
    clients[n_clients].fd = c_sock;
    max_sock = c_sock > max_sock ? c_sock : max_sock;
    char *fmt = "server: client %d just arrived\n";
    char msg[(strlen(fmt) - 2) + 4 + 1];
    sprintf(msg, fmt, clients[n_clients].id);
    n_clients++;
    broadcast(clients, msg);
}

void rem_client(client_t *c)
{
    char *fmt = "server: client %d just left\n";
    char msg[(strlen(fmt) - 2) + 4 + 1];
    sprintf(msg, fmt, c->id);
    FD_CLR(c->fd, &active);
    close(c->fd);
    if (c->rbuf) free(c->rbuf);
    if (c->wbuf) free(c->wbuf);
    c->rbuf = NULL;
    c->wbuf = NULL;
    c->id = -1;
    c->fd = -1;
    broadcast(clients, msg);
}

void on_readable(client_t *c)
{
    char buf[11];
    char *line;
    ssize_t read_bytes = recv(c->fd, buf, 10, 0);
    if (read_bytes <= 0) rem_client(c);
    else {
        if (!c->rbuf) c->rbuf = calloc(11, sizeof(char));
        else c->rbuf = realloc(c->rbuf, strlen(c->rbuf) + 11);
        buf[read_bytes] = 0;
        strcat(c->rbuf, buf);
        int has_line = extract_line(&c->rbuf, &line);
        if (has_line) {
            while (has_line) {
                char *fmt = "client %d: %s";
                char msg[(strlen(fmt) - 4) + strlen(line) + FD_SETSIZE + 1];
                sprintf(msg, fmt, c->id, line);
                broadcast(clients, msg);
                free(line);
                has_line = extract_line(&c->rbuf, &line);
            }
            if (c->rbuf && !c->rbuf[0]) {
                free(c->rbuf);
                c->rbuf = NULL;
            }
        }
    }
}

void on_writable(client_t *c)
{
    if (!c->wbuf) return;
    ssize_t sent_bytes = send(c->fd, c->wbuf, strlen(c->wbuf), 0);
    if (sent_bytes <= 0) rem_client(c);
    else if ((size_t)sent_bytes == strlen(c->wbuf)) {
        free(c->wbuf);
        c->wbuf = NULL;
    }
    else {
        char *newbuf = malloc(strlen(c->wbuf) - sent_bytes + 1);
        newbuf = strcpy(newbuf, c->wbuf + sent_bytes);
        free(c->wbuf);
        c->wbuf = newbuf;
    }
}

void init_serv(char* arg)
{
    bzero(clients, sizeof(clients));
    n_clients = 0;
    uint16_t port = atoi(arg);
    uint32_t ip = (1 << 24) | (0 << 16) | (0 << 8) | 127;
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = ip,
        .sin_port = htons(port)
    };

    sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
        panic("Fatal error (socket)\n");
    if ((bind(sock, (const struct sockaddr*)&addr, sizeof(struct sockaddr))) != 0)
        panic("Fatal error (bind)\n");
	if (listen(sock, 10) != 0) // change val
        panic("Fatal error (listen)\n");

    max_sock = sock;
    FD_ZERO(&active);
    FD_SET(sock, &active);
}


int main(int ac, char **av)
{
    if (ac != 2) panic("Wrong number of arguments\n");

    init_serv(av[1]);

    while (1) {
        FD_ZERO(&wset);
        FD_ZERO(&rset);
        rset = active;

        for (int i = 0; i < n_clients; ++i) {
            if (clients[i].id < 0) continue;
            client_t *c = &(clients[i]);
            if (FD_ISSET(c->fd, &active) && c->fd != sock && c->wbuf)
                FD_SET(c->fd, &wset);
        }
        
        if (select(max_sock + 1, &rset, &wset, NULL, NULL) < 0)
            panic("Fatal error (select)\n");
        if (FD_ISSET(sock, &rset)) {
            int c_sock = accept(sock, NULL, NULL);
            if (c_sock == -1) panic("Fatal error\n");
            add_client(c_sock);
        }
        for (int i = 0; i < n_clients; ++i) {
            if (clients[i].id < 0) continue;
            if (FD_ISSET(clients[i].fd, &rset))
                on_readable(&clients[i]);
        }
		for (int i = 0; i < n_clients; i++) {
            if (clients[i].id < 0) continue;
            if (FD_ISSET(clients[i].fd, &wset) && clients[i].fd != sock)
                on_writable(&clients[i]);
        }
    }
}
