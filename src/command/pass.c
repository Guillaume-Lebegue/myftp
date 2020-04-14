/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** pass
*/

#include <string.h>
#include "myftp.h"

int cmd_pass(server_t *server, list_socket_t *msocket, char **args)
{
    if (check_args(msocket, args, 2, false) != SUCCESS)
        return (SUCCESS);
    if (strcmp(args[1], msocket->user->password) == 0) {
        msocket->connected = true;
        send_message(msocket, 230, "User logged in, proceed.");
    } else if (!msocket->user) {
        send_message(msocket, 503, "Bad sequence of commands.");
    } else
        send_message(msocket, 530, "Not logged in.");
    return (SUCCESS);
}