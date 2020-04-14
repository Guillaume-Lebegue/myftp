/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** main
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "myftp.h"
#include "ftp_message.h"

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
    struct stat statbuf;

    if (access(path, W_OK | R_OK) != SUCCESS) {
        perror("Given default path");
        return (FAILURE);
    }
    if (stat(path, &statbuf) != 0) {
        perror("Given default path");
        return (FAILURE);
    }
    if (S_ISDIR(statbuf.st_mode))
        return (SUCCESS);
    fputs(ERROR_PARAM_DIR, stderr);
    return (FAILURE);
}

int get_port(short *port, char *given_port)
{
    char *endptr = "\0";

    *port = (short) strtol(given_port, &endptr, 10);
    if (endptr[0] != '\0') {
        fputs(ERROR_PARAM_PORT_NUM, stderr);
        return FAILURE;
    }
    return SUCCESS;
}

int main(int ac, char **av)
{
    short port = 0;

    if (ac >= 2 && strcmp(av[1], "-help") == 0)
        help();
    else if (ac != 3) {
        wrong_use();
        return (FAILURE);
    }
    if (ac == 3 && check_given_path(av[2]) == SUCCESS &&
            get_port(&port, av[1]) == SUCCESS) {
        start_server(port, av[2]);
    } else
        return FAILURE;
    return (SUCCESS);
}