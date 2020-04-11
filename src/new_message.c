/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** new_message
*/

#include <stdio.h>
#include "myftp.h"
#include "ftp_message.h"

int new_message(server_t *server, list_socket_t *msocket)
{
    char *mess = read_from_fd(msocket->fp, 10);
    int ret = SUCCESS;

    if (!mess) {
        fputs(ERROR_SOCKET_READING, stderr);
        return (FAILURE);
    }
    if (mess[0] == '\0') {
        do_disconnect(server, msocket);
        ret = DECONNECTION;
    }
    printf("new message: -%s-\n", mess);
    free(mess);
    return (ret);
}