/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** list_socket_utils
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "myftp.h"

list_socket_t *create_node_socket(int fd, socket_type_t type)
{
    list_socket_t *new = malloc(sizeof(list_socket_t));

    if (!new || fd == (-FAILURE))
        return (NULL);
    new->dirr_path = NULL;
    new->address = NULL;
    new->fd = fd;
    new->fp = fdopen(fd, "r+");
    if (!new->fp) {
        perror("Create node socket");
        return NULL;
    }
    new->type = type;
    new->next = NULL;
    return (new);
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

static void free_one_socket(list_socket_t *sock)
{
    close(sock->fd);
    fclose(sock->fp);
    if (sock->address)
        free(sock->address);
    free(sock);
}

void delete_list_socket(list_socket_t **list)
{
    list_socket_t *tmp1;

    while (*list) {
        tmp1 = (*list)->next;
        free_one_socket((*list));
        (*list) = tmp1;
    }
}

int delete_in_list_socket(list_socket_t **list, list_socket_t *ptr)
{
    list_socket_t *tmp;

    if (*list == ptr) {
        *list = ptr->next;
        free_one_socket(ptr);
        return (SUCCESS);
    }
    for (tmp = *list; tmp->next && tmp->next != ptr; tmp = tmp->next);
    if (!tmp->next)
        return (FAILURE);
    tmp->next = ptr->next;
    free_one_socket(ptr);
    return (SUCCESS);
}