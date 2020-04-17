/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** pass
*/

#include <string.h>
#include "myftp.h"

int spe_check_args(list_socket_t *msocket, char **args)
{
    int len = 0;

    for (; args[len]; len++);
    if (len == 1 || len == 2)
        return (SUCCESS);
    send_message(msocket, 501, "Wrong use of command.");
    return (FAILURE);
}

int cmd_pass(server_t *server, list_socket_t *msocket, char **args)
{
    if (spe_check_args(msocket, args) != SUCCESS)
        return (SUCCESS);
    if ((msocket->user->password[0] == '\0' && !args[1]) ||
            strcmp(args[1], msocket->user->password) == 0) {
        msocket->connected = true;
        send_message(msocket, 230, "User logged in, proceed.");
    } else if (!msocket->user) {
        send_message(msocket, 503, "Bad sequence of commands.");
    } else
        send_message(msocket, 530, "Not logged in.");
    return (SUCCESS);
}