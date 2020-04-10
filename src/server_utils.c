/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** server_utils
*/

#include <stdio.h>
#include <time.h>
#include <sys/select.h>
#include "myftp.h"

int set_fd_set(int max, fd_set *set, list_socket_t *list, socket_type_t type)
{
    FD_ZERO(set);
    for (list_socket_t *tmp = list; tmp; tmp = tmp ->next) {
        if (tmp->type != type)
            continue;
        FD_SET(tmp->fd, set);
        max = max <= tmp->fd ? tmp->fd + 1 : max;
    }
    return (max);
}

void server_log(char *msg)
{
    time_t timer;
    char buffer[26];
    struct tm *tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%d/%m/%y-%H:%M", tm_info);
    printf("[%s][myftp] %s\n", buffer, msg);
}