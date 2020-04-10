/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** socket_utils
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include "myftp.h"

int start_listen(int sfd)
{
    if (listen(sfd, QUEUE_LENGTH) == -1) {
        perror("start_listen");
        return (FAILURE);
    }
    return (SUCCESS);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"

int bind_socket_tcp(int sfd, unsigned short port)
{
    struct sockaddr_in conf = {AF_INET, htons(port), INADDR_ANY};

    if (bind(sfd, (struct sockaddr *) &conf,
            sizeof(struct sockaddr_in)) == -1) {
        perror("bind_socket");
        return (FAILURE);
    }
    return (SUCCESS);
}

#pragma GCC diagnostic pop

int start_socket(void)
{
    int sfd = 0;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("start_socket");
        return (-FAILURE);
    }
    return (sfd);
}