/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** cdup
*/

#include <string.h>
#include "myftp.h"

static void remove_last_slash(char *str, int len)
{
    for (; len >= 0 && str[len] != '/'; len--);
    str[len] = '\0';
}

static char *add_last_slash(list_socket_t *msocket, char *path)
{
    if (path[0] == '\0')
        path = add_slash(msocket, path);
    return (path);
}

int cmd_cdup(server_t *server, list_socket_t *msocket, char **args)
{
    int len = strlen(msocket->dirr_path);

    if (check_args(msocket, args, 1, true) != SUCCESS)
        return (SUCCESS);
    if (len == 1) {
        send_message(msocket, 550, "No such file or directory.");
        return (SUCCESS);
    }
    remove_last_slash(msocket->dirr_path, len - 1);
    msocket->dirr_path = add_last_slash(msocket, msocket->dirr_path);
    send_message(msocket, 250, "Okay.");
    return (SUCCESS);
}