/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** new_message
*/

#include <stdio.h>
#include <string.h>
#include "myftp.h"
#include "ftp_message.h"
#include "ftp_commands.h"

static int select_action(server_t *server, list_socket_t *msocket, char **args)
{
    int pos = search_in_list(COMMAND_STR, args[0]);

    if (pos == -1) {
        send_message(msocket, 502, "Command not implemented.");
        return (FAILURE);
    }
    return (COMMAND_CMD[pos](server, msocket, args));
}

int new_message(server_t *server, list_socket_t *msocket)
{
    char *mess = remove_last_char(read_from_fd(msocket->fp, 10));
    printf("message: %s, datafd: %d\n", mess, msocket->datafd);
    char **args = (!mess || mess[0] == '\0') ? NULL : strtotab(mess, ' ');
    int ret = SUCCESS;

    if (!mess || (mess[0] != '\0' && !args)) {
        fputs(ERROR_SOCKET_READING, stderr);
        return (FAILURE);
    }
    if (mess[0] == '\0') {
        do_disconnect(server, msocket);
        ret = DISCONECT;
    } else
        ret = select_action(server, msocket, args);
    free(args);
    free(mess);
    return (ret);
}