/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** list_socket_utils
*/

#include <stdlib.h>
#include <unistd.h>
#include "myftp.h"

list_socket_t *create_node_socket(int fd, socket_type_t type)
{
    list_socket_t *new = malloc(sizeof(list_socket_t));

    if (!new)
        return (NULL);
    new->dirr_path = NULL;
    new->fd = fd;
    new->type = type;
    new->next = NULL;
    return (new);
}

list_socket_t *search_node_socket(list_socket_t *list, int fd)
{
    list_socket_t *tmp;

    for (tmp = list; tmp && tmp->fd != fd; tmp = tmp->next);
    return tmp;
}

int add_in_list_socket(list_socket_t **list, list_socket_t *new)
{
    list_socket_t *tmp;

    if (!new)
        return (FAILURE);
    if (!*list) {
        *list = new;
        return (SUCCESS);
    }
    for (tmp = *list; tmp->next; tmp = tmp->next);
    tmp->next = new;
    return (SUCCESS);
}

void delete_list_socket(list_socket_t **list)
{
    list_socket_t *tmp1;

    while (*list) {
        tmp1 = (*list)->next;
        close((*list)->fd);
        free((*list));
        (*list) = tmp1;
    }
}

int delete_in_list_socket(list_socket_t **list, list_socket_t *ptr)
{
    list_socket_t *tmp;

    if (*list == ptr) {
        *list = ptr->next;
        close(ptr->fd);
        free(ptr);
        return (SUCCESS);
    }
    for (tmp = *list; tmp->next && tmp->next != ptr; tmp = tmp->next);
    if (!tmp->next)
        return (FAILURE);
    tmp->next = ptr->next;
    close(ptr->fd);
    free(ptr);
    return (SUCCESS);
}