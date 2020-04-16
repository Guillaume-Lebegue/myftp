/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** noop
*/

#include "myftp.h"

int cmd_noop(server_t *server, list_socket_t *msocket, char **args)
{
    if (check_args(msocket, args, 1, false) != SUCCESS)
        return (SUCCESS);
    send_message(msocket, 200, "... Why do you try that");
    return (SUCCESS);
}