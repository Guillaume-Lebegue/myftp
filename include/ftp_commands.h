/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** ftp_commands
*/

#ifndef FTP_COMMANDS_H_
#define FTP_COMMANDS_H_

#include "myftp.h"

int cmd_user(server_t *server, list_socket_t *msocket, char **args);
int cmd_syst(server_t *server, list_socket_t *msocket, char **args);
int cmd_pass(server_t *server, list_socket_t *msocket, char **args);
int cmd_pwd(server_t *server, list_socket_t *msocket, char **args);
int cmd_cwd(server_t *server, list_socket_t *msocket, char **args);
int cmd_cdup(server_t *server, list_socket_t *msocket, char **args);
int cmd_quit(server_t *server, list_socket_t *msocket, char **args);
int cmd_dele(server_t *server, list_socket_t *msocket, char **args);
int cmd_noop(server_t *server, list_socket_t *msocket, char **args);
int cmd_pasv(server_t *server, list_socket_t *msocket, char **args);
int cmd_port(server_t *server, list_socket_t *msocket, char **args);

static const char *COMMAND_STR[] = {
    "USER",
    "SYST",
    "PASS",
    "PWD",
    "CWD",
    "CDUP",
    "QUIT",
    "DELE",
    "NOOP",
    "PASV",
    "PORT",
    "HELP",
    "RETR",
    "STOR",
    "LIST"
};

static const int (*COMMAND_CMD[])
    (server_t *server, list_socket_t *msocket, char **args) = {
    cmd_user,
    cmd_syst,
    cmd_pass,
    cmd_pwd,
    cmd_cwd,
    cmd_cdup,
    cmd_quit,
    cmd_dele,
    cmd_noop,
    cmd_pasv,
    cmd_port,
    NULL,
    NULL,
    NULL,
    NULL
};

static const int MAX_CMD_INDEX = 10;

#endif /* !FTP_COMMANDS_H_ */
