/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** pwd
*/

#include <stdlib.h>
#include <string.h>
#include "myftp.h"

int cmd_pwd(server_t *server, list_socket_t *msocket, char **args)
{
    char *msg;

    if (check_args(msocket, args, 1, true) != SUCCESS)
        return (SUCCESS);
    msg = malloc(sizeof(char) * (strlen(msocket->dirr_path) + 29));
    if (!msg)
        return (error_malloc(msocket, "cwd_pwd"));
    sprintf(msg, "\"%s\" is the current directory.", msocket->dirr_path);
    send_message(msocket, 257, msg);
    free(msg);
    return (SUCCESS);
}