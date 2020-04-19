/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** string_utils
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/limits.h>

int count_occ(char *str, char search)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == search)
            count++;
    }
    return (count);
}

char **strtotab(char *str, char delim)
{
    int num_case = count_occ(str, delim) + 1;
    char **tab = malloc(sizeof(char *) * (num_case + 1));
    char ddelim[2] = " ";

    if (!tab) {
        perror("strtotab");
        return (NULL);
    }
    ddelim[0] = delim;
    for (int i = 0; i != num_case; i++) {
        tab[i] = strtok(i ? NULL : str, ddelim);
    }
    tab[num_case] = NULL;
    return (tab);
}

char *remove_last_char(char *str)
{
    if (!str)
        return (NULL);
    if (str[0] == '\0')
        return (str);
    if (str[strlen(str) - 1] == '\r')
        str[strlen(str) - 1] = '\0';
    return (str);
}

int search_in_list(const char **tab, char *search)
{
    int pos;

    if (!search)
        return (-1);
    for (pos = 0; tab[pos]; pos++) {
        if (strcmp(tab[pos], search) == 0)
            break;
    }
    if (tab[pos])
        return (pos);
    return (-1);
}

char *absolute_path(char *rel_path)
{
    char *resolved_path;

    resolved_path = realpath(rel_path, NULL);
    if (!resolved_path)
        perror("absolute_path");
    return (resolved_path);
}