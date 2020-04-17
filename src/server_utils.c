/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** server_utils
*/

#include <stdio.h>
#include <time.h>
#include <sys/select.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "myftp.h"
#include "ftp_message.h"

int set_rfd_set(int max, fd_set *set, list_socket_t *list)
{
    FD_ZERO(set);
    for (list_socket_t *tmp = list; tmp; tmp = tmp ->next) {
        if (tmp->type != SERVER && tmp->type != CLIENT)
            continue;
        FD_SET(tmp->fd, set);
        max = max <= tmp->fd ? tmp->fd + 1 : max;
    }
    return (max);
}

void server_log(const char *msg)
{
    time_t timer;
    char buffer[26];
    struct tm *tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%d/%m/%y-%H:%M", tm_info);
    printf("[%s][myftp] %s\n", buffer, msg);
}

char *read_from_fd(FILE *fp, size_t size)
{
    char *str;
    int ch;
    size_t len = 0;

    str = realloc(NULL, sizeof(char) * size);
    if (!str)
        return (str);
    ch = fgetc(fp);
    while (EOF != ch && ch != '\n') {
        str[len++] = ch;
        if (len == size) {
            str = realloc(str, sizeof(char) * (size += 16));
            if (!str)
                return (str);
        }
        ch = fgetc(fp);
    }
    str[len++] = '\0';
    return (realloc(str, sizeof(char)*len));
}

void do_disconnect(server_t *server, list_socket_t *deco_sock)
{
    char str[50];

    sprintf(str, "Disconnection from: %s", deco_sock->address);
    server_log(str);
    if (delete_in_list_socket(&server->list_socket, deco_sock) == FAILURE)
        fputs(ERROR_SOCKET_NOTFOUND, stderr);
}

int send_message(list_socket_t *socket, const int code, const char *msg)
{
    char *res;
    int len = 4 + strlen(msg);

    for (int i = 1; code / i; i *= 10, len++);
    res = malloc(sizeof(char) * len);
    if (!res)
        return (FAILURE);
    sprintf(res, "%d %s\r\n", code, msg);
    write(socket->fd, res, len - 1);
    free(res);
    return (SUCCESS);
}