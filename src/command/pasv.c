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

    msocket->datafd = start_socket();
    if (msocket->datafd == (-FAILURE))
        return (FAILURE);
    if (bind(msocket->datafd, (struct sockaddr *) &conf,
            sizeof(struct sockaddr_in)) == -1) {
        error_malloc(msocket, "bind_socket for data");
        return (FAILURE);
    }
    return (SUCCESS);
}

#pragma GCC diagnostic pop

static char *get_add_format(list_socket_t *msocket, struct sockaddr_in *conf)
{
    char *full_addr;
    char *sep_addr[4];
    int port = ntohs(conf->sin_port);
    char *res = malloc(sizeof(char) * (36 + 7));
    int p1 = port >> 8;
    int p2 = port - (p1 * 256);

    if (!res) {
        error_malloc(msocket, "get format for pasv");
        return (NULL);
    }
    full_addr = inet_ntoa(conf->sin_addr);
    for (int i = 0; i != 4; i++)
        sep_addr[i] = strtok(i == 0 ? full_addr : NULL, ".");
    sprintf(res, "=%s,%s,%s,%s,%d,%d", sep_addr[0], sep_addr[1], sep_addr[2],
        sep_addr[3], p1, p2);
    return (res);
}

void data_log(struct sockaddr_in *conf)
{
    char *add;
    char str[50];

    sprintf(str, "%s:%i", inet_ntoa(conf->sin_addr),
        ntohs(conf->sin_port));
    add = strdup(str);
    sprintf(str, "Pasive data oppened on: %s", add);
    server_log(str);
    free(add);
}

int cmd_pasv(server_t *server, list_socket_t *msocket, char **args)
{
    char *msg;
    struct sockaddr_in conf;
    uint confl = sizeof(struct sockaddr_in);

    if (check_args(msocket, args, 1, true) != SUCCESS)
        return (SUCCESS);
    if (create_new_sock(msocket) != SUCCESS)
        return (SUCCESS);
    if (getsockname(msocket->datafd, (struct sockaddr *) &conf, &confl) != 0) {
        error_malloc(msocket, "cmd_pasv");
        return (SUCCESS);
    }
    msg = get_add_format(msocket, &conf);
    if (!msg)
        return (SUCCESS);
    send_message(msocket, 227, msg);
    data_log(&conf);
    free(msg);
    return (SUCCESS);
}