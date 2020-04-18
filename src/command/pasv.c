/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** pasv
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include "myftp.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"

static int create_new_sock(list_socket_t *msocket)
{
    struct sockaddr_in conf = {AF_INET, htons(0), INADDR_ANY};
    int listen_fd;

    listen_fd = start_socket();
    if (listen_fd == (-FAILURE))
        return (listen_fd);
    if (bind(listen_fd, (struct sockaddr *) &conf,
            sizeof(struct sockaddr_in)) == -1 ||
            listen(listen_fd, 1)) {
        error_malloc(msocket, "bind_socket for data");
        return (-FAILURE);
    }
    return (listen_fd);
}

#pragma GCC diagnostic pop

static char *get_add_format(list_socket_t *msocket, int listen_fd)
{
    char *full_addr = get_remote_addr(msocket->fd);
    char *sep_addr[4];
    int port = get_local_port(listen_fd);
    char *res = malloc(sizeof(char) * (36 + 7));

    if (!full_addr || port == -FAILURE || !res) {
        error_malloc(msocket, "get_add_format");
        return (NULL);
    }
    for (int i = 0; i != 4; i++)
        sep_addr[i] = strtok(i == 0 ? full_addr : NULL, ".");
    sprintf(res, "=%s,%s,%s,%s,%d,%d", sep_addr[0], sep_addr[1], sep_addr[2],
        sep_addr[3], port / 256, port % 256);
    free(full_addr);
    return (res);
}

static int send_add(list_socket_t *msocket, int listen_fd)
{
    char *msg;

    msg = get_add_format(msocket, listen_fd);
    if (!msg)
        return (FAILURE);
    send_message(msocket, 227, msg);
    free(msg);
    return (SUCCESS);
}

int data_connect(list_socket_t *msocket)
{
    struct sockaddr_in res_conf;
    uint addr_len = sizeof(struct sockaddr_in);
    char str[50];

    msocket->datafd = accept(msocket->listenfd,
        (struct sockaddr *) &res_conf, &addr_len);
    if (msocket->datafd == -1) {
        error_malloc(msocket, "data_connect");
        return (FAILURE);
    }
    sprintf(str, "Data connection from: %s:%i", inet_ntoa(res_conf.sin_addr),
        ntohs(res_conf.sin_port));
    server_log(str);
    close(msocket->listenfd);
    msocket->listenfd = -1;
    return (SUCCESS);
}

int cmd_pasv(server_t *server, list_socket_t *msocket, char **args)
{
    int listen_fd;

    if (check_args(msocket, args, 1, true) != SUCCESS)
        return (SUCCESS);
    if (msocket->datafd != -1) {
        close(msocket->datafd);
        msocket->datafd = -1;
    }
    listen_fd = create_new_sock(msocket);
    if (listen_fd == -FAILURE)
        return (SUCCESS);
    if (send_add(msocket, listen_fd) != SUCCESS) {
        close(listen_fd);
        return (SUCCESS);
    }
    msocket->listenfd = listen_fd;
    return (SUCCESS);
}