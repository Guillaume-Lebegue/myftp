/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** syst
*/

#include "myftp.h"

int cmd_syst(server_t *server, list_socket_t *msocket, char **args)
{
    send_message(msocket, 215, "UNIX Type: L8");
    return (SUCCESS);
}