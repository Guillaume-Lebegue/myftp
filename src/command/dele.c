/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** dele
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "myftp.h"

static char *get_full_path(list_socket_t *msocket, char *given_path)
{
    int full_size = strlen(msocket->user->dirr_path) + strlen(given_path);
    char *full_path;

    if (given_path[0] != '/')
        full_size += strlen(msocket->dirr_path) + 1;
    full_path = malloc(sizeof(char) * (full_size + 1));
    if (!full_path) {
        error_malloc(msocket, "get_full_path");
        return (NULL);
    }
    full_path[0] = '\0';
    full_path = strcat(full_path, msocket->user->dirr_path);
    if (given_path[0] != '/')
        full_path = strcat(strcat(full_path, msocket->dirr_path), "/");
    full_path = strcat(full_path, given_path);
    return (full_path);
}

static int check_exist_path(char *path)
{
    struct stat statbuf;

    printf("access\n");
    if (access(path, W_OK | R_OK) != SUCCESS)
        return (FAILURE);
    printf("stat\n");
    if (stat(path, &statbuf) != 0)
        return (FAILURE);
    printf("is reg file ?\n");
    if (S_ISREG(statbuf.st_mode))
        return (SUCCESS);
    printf("no\n");
    return (FAILURE);
}

static char *do_path_check(list_socket_t *msocket, char *given_path)
{
    char *given_full;
    char *given_clean;

    given_full = get_full_path(msocket, given_path);
    if (!given_full)
        return (NULL);
    printf("full path: %s\n", given_full);
    if (check_exist_path(given_full) != SUCCESS) {
        send_message(msocket, 550, "No such file.");
        return (NULL);
    }
    printf("exist\n");
    given_clean = absolute_path(given_full);
    if (!given_clean || !prefix(msocket->user->dirr_path, given_clean)) {
        send_message(msocket, 550, "No such file.");
        return (NULL);
    }
    printf("absolute path: %s\n", given_clean);
    free(given_full);
    return (given_clean);
}

static int delete_file(list_socket_t *msocket, char *filepath)
{
    if (remove(filepath) != 0) {
        send_message(msocket, 550, "File coundn't be removed");
        perror("delete_file");
        return (FAILURE);
    }
    return (SUCCESS);
}

int cmd_dele(server_t *server, list_socket_t *msocket, char **args)
{
    char *full_path;

    if (check_args(msocket, args, 2, true) != SUCCESS)
        return (SUCCESS);
    full_path = do_path_check(msocket, args[1]);
    printf("to delete: %s\n", full_path);
    if (!full_path || delete_file(msocket, full_path) != SUCCESS)
        return (SUCCESS);
    send_message(msocket, 250, "Okay.");
    free(full_path);
    return (SUCCESS);
}