/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** port
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "myftp.h"

static int get_address(struct in_addr *address, char *str_addr)
{
    char *sep_add[4];
    char form_addr[50];

    for (int i = 0; i < 4; i++) {
        sep_add[i] = strtok(!i ? str_addr : NULL, ",");
        if (!sep_add[i])
            return (FAILURE);
    }
    sprintf(form_addr, "%s.%s.%s.%s", sep_add[0], sep_add[1], sep_add[2],
        sep_add[3]);
    if (inet_aton(form_addr, address) == 0)
        return (FAILURE);
    return (SUCCESS);
}

static int get_port(in_port_t *port)
{
    int dec_port[2];
    char *tmp;

    for (int i = 0; i < 2; i++) {
        tmp = strtok(NULL, ",");
        if (!tmp)
            return (FAILURE);
        dec_port[i] = atoi(tmp);
    }
    *port = htons(dec_port[0] * 256 + dec_port[1]);
    return (SUCCESS);
}

static int store_data(list_socket_t *msocket, char *addr)
{
    struct in_addr address;
    in_port_t port;

    if (msocket->data_info)
        free(msocket->data_info);
    msocket->data_info = malloc(sizeof(struct sockaddr_in));
    if (get_address(&address, addr) != SUCCESS ||
            get_port(&port) != SUCCESS || !msocket->data_info)
        return (FAILURE);
    msocket->data_info->sin_family = AF_INET;
    msocket->data_info->sin_port = port;
    msocket->data_info->sin_addr = address;
    return (SUCCESS);
}

int cmd_port(server_t *server, list_socket_t *msocket, char **args)
{
    if (check_args(msocket, args, 2, true) != SUCCESS)
        return (SUCCESS);
    if (msocket->datafd != -1)
        close(msocket->datafd);
    msocket->datafd = start_socket();
    if (msocket->datafd == -FAILURE ||
            store_data(msocket, args[1]) == FAILURE) {
        error_malloc(msocket, "cmd_port");
        return (SUCCESS);
    }
    send_message(msocket, 200, "Okay.");
    return (SUCCESS);
}