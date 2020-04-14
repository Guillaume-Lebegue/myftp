/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** users_utils
*/

#include <stdlib.h>
#include <string.h>
#include "myftp.h"

user_t *create_user(char *name, char *pass, char *dirr, user_level_t level)
{
    user_t *new = malloc(sizeof(user_t));

    if (!new)
        return (NULL);
    new->name = strdup(name);
    new->password = strdup(pass);
    new->level = level;
    new->dirr_path = strdup(dirr);
    return (new);
}

void free_user(user_t *user)
{
    free(user->name);
    free(user->password);
    free(user->dirr_path);
    free(user);
}

void free_list_user(user_t **users)
{
    for (int i = 0; users[i]; i++)
        free_user(users[i]);
    free(users);
}

user_t *search_user(server_t *server, char *name)
{
    for (int i = 0; server->users[i]; i++)
        if (strcmp(server->users[i]->name, name) == 0)
            return (server->users[i]);
    return (NULL);
}