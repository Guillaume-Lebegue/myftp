/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** new_connect
*/

#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include "myftp.h"
#include "ftp_message.h"

static int do_accept(list_socket_t *to_accept, char **address)
{
    struct sockaddr_in res_conf;
    uint addr_len = sizeof(struct sockaddr_in);
    int resfd = 0;
    char str[50];

    resfd = accept(to_accept->fd, (struct sockaddr *) &res_conf, &addr_len);
    if (resfd == -1)
        return ((-FAILURE));
    sprintf(str, "%s:%i", inet_ntoa(res_conf.sin_addr),
        ntohs(res_conf.sin_port));
    *address = strdup(str);
    sprintf(str, "Connection from: %s", *address);
    server_log(str);
    return (resfd);
}

int new_connect(server_t *server, list_socket_t *ssocket)
{
    list_socket_t *new = NULL;
    char *address;

    new = create_node_socket(do_accept(ssocket, &address), CLIENT);
    if (!new) {
        delete_list_socket(&new);
        return (FAILURE);
    }
    new->address = address;
    add_in_list_socket(&server->list_socket, new);
    send_message(new, 220, WELCOME_MESSAGE);
    return (SUCCESS);
}