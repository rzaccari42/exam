/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:22:43 by razaccar          #+#    #+#             */
/*   Updated: 2026/03/10 14:41:49 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    int     sockfd;
    char*   buf;
} client_t;

void panic(char* err)
{
    write(STDERR_FILENO, err, strlen(err));
    exit(1); 
}


void broadcast(client_t* clients, char* message)  
{
    while (clients) {
        (*clients).buf = message;
        clients++;
    }
}

int main(int ac, char** av)
{
    if (ac != 2)
        panic("Wrong number of arguments\n");

    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == -1)
        panic("Fatal error (socket)\n");

    uint16_t arg = atoi(av[1]);

    uint32_t addr = (1 << 24) | (0 << 16) | (0 << 8) | 127;
    uint16_t port = ((arg >> 8) & 0x00FF) | ((arg << 8) & 0xFF00);
    
    uint8_t ip_parts[4];
    ip_parts[0] = addr >> 24;
    ip_parts[1] = addr >> 16;
    ip_parts[2] = addr >> 8;
    ip_parts[3] = addr >> 0;
    printf("IP:   %d.%d.%d.%d\n", ip_parts[3], ip_parts[2], ip_parts[1], ip_parts[0]);
    printf("PORT: %d\n", ntohs(port));

    struct sockaddr_in server, client;
	bzero(&server, sizeof (struct sockaddr_in)); 
	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = addr;
	server.sin_port = port; 

    if ((bind(listen_sock, (const struct sockaddr*)&server, sizeof(struct sockaddr))) != 0)
        panic("Fatal error (bind)\n");
	if (listen(listen_sock, 10) != 0)
        panic("Fatal error (listen)\n");

    client_t* clients = calloc(FD_SETSIZE, sizeof(client_t));

    int n_sock = 1; 
    fd_set sock_set, read_set, write_set;
    FD_ZERO(&sock_set);
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    FD_SET(listen_sock, &sock_set);

    struct timeval  tv;
    tv.tv_sec = 1;

    while (1) {
        read_set = sock_set;
        write_set = sock_set;
        int ready = select(n_sock + 1, &read_set, &write_set, NULL, &tv);
        switch (ready) {
            case -1: panic("Fatal error (select)\n");
            case 0:
                printf("continue\n");
            default:
                if (FD_ISSET(listen_sock, &read_set)) {
                    int fd = accept(listen_sock, NULL, NULL);
                    if (fd == -1) panic("Fatal error\n");
                    clients[n_sock].sockfd = fd;
                    clients[n_sock].id = n_sock;
                    n_sock += 1;
                    FD_SET(fd, &sock_set);
                    char* message = NULL;
                    sprintf(message, "server: client %d just arrived\n", clients[n_sock].id);
                    broadcast(clients, message);
                }
                for (int i = 0; i < n_sock; ++i) {
                    client_t c = clients[i];
                    char* message;
                    if (FD_ISSET(c.sockfd, &read_set)) {
                        char* line = malloc(11 * sizeof(char));
                        ssize_t read_bytes = recv(c.sockfd, c.buf, 10, 0);
                        if (!read_bytes) {
                            sprintf(message, "server: client %d just left", c.id);
                            broadcast(clients, message);
                        }
                        while (read_bytes > 0) {
                            strcat(line, c.buf);
                            read_bytes = recv(c.sockfd, c.buf, 10, 0);
                        }
                        sprintf(message, "client %d: %s", c.id, line);
                        broadcast(clients, message);
                        free(line);
                        free(message);
                    }
                    if (FD_ISSET(c.sockfd, &write_set)) {
                        send(c.sockfd, c.buf, strlen(c.buf), 0);
                        free(c.buf);
                    }
                }
        }
    }

}

// uint16_t htons(uint16_t n) 
// {
// }
//
// uint32_t htonl(uint32_t n)
// {
// }
// 
// void event_loop()
// {
// }
