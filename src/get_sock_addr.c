/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** get_sock_addr
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "myftp.h"

char *get_remote_addr(int socket_fd)
{
    static struct sockaddr_in address;
    socklen_t size = sizeof(address);
    char *tmp;

    if (getpeername(socket_fd, (struct sockaddr *)&address, &size) == -1)
        return (NULL);
    tmp = inet_ntoa(address.sin_addr);
    if (!tmp)
        return (NULL);
    return (strdup(tmp));
}

unsigned short get_local_port(int socket_fd)
{
    static struct sockaddr_in address;
    socklen_t size = sizeof(address);

    if (getsockname(socket_fd, (struct sockaddr *)&address, &size) == -1)
        return (-FAILURE);
    return (ntohs(address.sin_port));
}