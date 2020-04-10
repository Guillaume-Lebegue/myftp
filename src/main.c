/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** main
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "myftp.h"

void help(void)
{
    puts("USAGE: ./myftp port path");
    puts("\tport is the port number on wich the server socket listens");
    puts("\tpath is the path to the home directory for the Anonymous user");
}

void wrong_use(void)
{
    puts("Wrong use. see help with: './myftp -help'");
}

int check_given_path(char *path)
{
    if (access(path, W_OK | R_OK | X_OK) != SUCCESS) {
        perror("Given default path");
        return (FAILURE);
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac >= 2 && strcmp(av[1], "-help") == 0)
        help();
    else if (ac != 3) {
        wrong_use();
        return (FAILURE);
    }
    if (ac == 3 && check_given_path(av[2]) == 0) {
        puts("go to server");
    } else
        return FAILURE;
    return (SUCCESS);
}