/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** base_server
*/

#include <stdlib.h>
#include <stdio.h>
#include "myftp.h"
#include "ftp_message.h"

static int init_server(short port, char *d_path, server_t *server, int *stop)
{
    server->users = malloc(sizeof(user_t *) * 2);
    server->users[0] = create_user("Anonymous", "", d_path, USER);
    server->users[1] = NULL;
    server->list_socket = create_node_socket(start_socket(), SERVER);
    if (server->list_socket->fd == (-FAILURE) || !server->users[0] ||
            bind_socket_tcp(server->list_socket->fd, port) == FAILURE ||
            start_listen(server->list_socket->fd) == FAILURE ||
            setup_catcher(stop)) {
        server_log(ERROR_SERVER_START);
        return (FAILURE);
    }
    server_log(INFO_SERVER_LISTEN);
    return (SUCCESS);
}

static void close_server(server_t *server)
{
    server_log(INFO_SERVER_CLOSE);
    delete_list_socket(&server->list_socket);
    free_list_user(server->users);
}

static int run_update(server_t *server, list_socket_t *actu)
{
    int new_mess_ret = SUCCESS;

    if (actu->type == SERVER) {
        if (new_connect(server, actu) == FAILURE)
            server_log(ERROR_CONNECT);
    } else {
        new_mess_ret = new_message(server, actu);
        if (new_mess_ret == FAILURE) {
            server_log(ERROR_MESSAGE);
            new_mess_ret = 0;
        }
    }
    return (new_mess_ret);
}

static void do_update(server_t *server, fd_set *updated)
{
    for (list_socket_t *tmp = server->list_socket; tmp; tmp = tmp->next) {
        if (FD_ISSET(tmp->fd, updated))
            if (run_update(server, tmp) != SUCCESS)
                return;
        if (FD_ISSET(tmp->listenfd, updated))
            data_connect(tmp);
    }
}

int start_server(short port, char *d_path)
{
    server_t server;
    fd_set rfds;
    int max_fd = 0;
    int i = 1;
    char *default_path = absolute_path(d_path);

    printf("default_path: %s\n", default_path);
    if (!default_path ||
            init_server(port, default_path, &server, &i) == FAILURE)
        return (FAILURE);
    while (i) {
        max_fd = set_rfd_set(max_fd, &rfds, server.list_socket);
        if (select(max_fd, &rfds, NULL, NULL, NULL) == -1) {
            perror("Server loop");
            break;
        }
        do_update(&server, &rfds);
    }
    close_server(&server);
    free(default_path);
    return (SUCCESS);
}