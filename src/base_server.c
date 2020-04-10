/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** base_server
*/

#include <stdlib.h>
#include <stdio.h>
#include "myftp.h"

static int init_server(short port, char *default_path, server_t *server)
{
    server->default_path = default_path;
    server->list_socket = create_node_socket(start_socket(), SERVER);
    if (server->list_socket->fd == (-FAILURE) ||
            bind_socket_tcp(server->list_socket->fd, port) == FAILURE ||
            start_listen(server->list_socket->fd) == FAILURE) {
        server_log("Server couldn't start");
        return (FAILURE);
    }
    server_log("Server now listening");
    return (SUCCESS);
}

static void close_server(server_t *server)
{
    server_log("Server now closing");
    delete_list_socket(&server->list_socket);
}

static void do_update(server_t *server, fd_set *updated)
{
    for (list_socket_t *tmp = server->list_socket; tmp; tmp = tmp->next) {
        if (FD_ISSET(tmp->fd, updated) && tmp->type == SERVER)
            if (new_connect(server, tmp) == FAILURE) {
                server_log("Error with new connect");
                continue;
            }
    }
}

int start_server(short port, char *default_path)
{
    server_t server;
    fd_set rfds;
    int max_fd = 0;

    if (init_server(port, default_path, &server) == FAILURE)
        return (FAILURE);
    while (1) {
        max_fd = set_fd_set(max_fd, &rfds, server.list_socket, SERVER);
        if (select(max_fd, &rfds, NULL, NULL, NULL) == -1) {
            perror("Server loop");
            break;
        }
        do_update(&server, &rfds);
    }
    close_server(&server);
    return (SUCCESS);
}