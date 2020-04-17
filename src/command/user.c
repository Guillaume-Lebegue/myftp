/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** user
*/

#include <stdio.h>
#include "myftp.h"

static int check_user(list_socket_t *msocket, user_t *user)
{
    if (user)
        return (SUCCESS);
    send_message(msocket, 530, "User not found");
    return (FAILURE);
}

int cmd_user(server_t *server, list_socket_t *msocket, char **args)
{
    user_t *user;

    if (check_args(msocket, args, 2, false) != SUCCESS)
        return (SUCCESS);
    user = search_user(server, args[1]);
    if (check_user(msocket, user) != SUCCESS)
        return (SUCCESS);
    msocket->user = user;
    msocket->connected = false;
    send_message(msocket, 331, "User name okay, need password");
    return (SUCCESS);
}