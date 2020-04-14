/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** command_utils
*/

#include <stdio.h>
#include "myftp.h"

int check_args(list_socket_t *msocket, char **args, int num_arg, bool logged)
{
    int len = 0;

    if (logged && !msocket->connected) {
        send_message(msocket, 530, "Not logged in.");
        return (FAILURE);
    }
    for (; args[len]; len++);
    if (len == num_arg)
        return (SUCCESS);
    send_message(msocket, 501, "Wrong use of command.");
    return (FAILURE);
}

int error_malloc(list_socket_t *msocket, char *msg)
{
    perror(msg);
    send_message(msocket, 550, "Server Error");
    return (SUCCESS);
}