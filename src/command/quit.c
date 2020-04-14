/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** quit
*/

#include "myftp.h"
#include "ftp_message.h"

int cmd_quit(server_t *server, list_socket_t *msocket, char **args)
{
    if (check_args(msocket, args, 1, false) != SUCCESS)
        return (SUCCESS);
    send_message(msocket, 221, BYE_MESSAGE);
    do_disconnect(server, msocket);
    return (DISCONECT);
}