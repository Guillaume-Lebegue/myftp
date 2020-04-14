/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** string_utils2
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "myftp.h"

bool prefix(const char *pre, const char *str)
{
    return (strncmp(pre, str, strlen(pre)) == 0);
}

char *add_slash(list_socket_t *msocket, char *path)
{
    if (!path)
        return (NULL);
    path = realloc(path, sizeof(char) * (strlen(path) + 2));
    if (!path) {
        if (msocket)
            error_malloc(msocket, "add_slash");
        return (NULL);
    }
    path = strcat(path, "/");
    return (path);
}