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

static int check_password(list_socket_t *msocket)
{
    if (msocket->user->password[0] == '\0') {
        msocket->connected = true;
        send_message(msocket, 230, "Logged in");
    } else
        send_message(msocket, 331, "User name okay, need password");
    return (SUCCESS);
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
    check_password(msocket);
    return (SUCCESS);
}