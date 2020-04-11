/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** catch_stop
*/

#include <signal.h>
#include <stdio.h>
#include "myftp.h"

static void catch_handler(int signal, siginfo_t *info, void *data)
{
    static int *stop = NULL;
    if (signal == -1)
        stop = (int *) data;
    else
        *stop = SUCCESS;
}

int setup_catcher(int *stop)
{
    struct sigaction sa;

    catch_handler(-1, NULL, stop);
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = catch_handler;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Setup signal catcher");
        return (FAILURE);
    }
    return (SUCCESS);
}