/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** myftp
*/

#ifndef MYFTP_H_
#define MYFTP_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static const int SUCCESS = 0;
static const int FAILURE = 84;
static const int DISCONECT = -1;

static const int QUEUE_LENGTH = 10;

typedef enum {
    SERVER,
    CLIENT
} socket_type_t;

typedef enum {
    ROOT,
    ADMIN,
    USER
} user_level_t;

typedef struct{
    char *name;
    char *password;
    char *dirr_path;
    user_level_t level;
} user_t;

typedef struct list_socket_s{
    struct list_socket_s *next;
    char *dirr_path;
    FILE *fp;
    char *address;
    user_t *user;
    bool connected;
    int fd;
    int datafd;
    int listenfd;
    socket_type_t type;
} list_socket_t;

typedef struct {
    list_socket_t *list_socket;
    user_t **users;
} server_t;

int start_server(short port, char *default_path);
int new_connect(server_t *server, list_socket_t *ssocket);
int new_message(server_t *server, list_socket_t *msocket);

void server_log(const char *msg);
int set_rfd_set(int max, fd_set *set, list_socket_t *list);
char *read_from_fd(FILE *fp, size_t size);
void do_disconnect(server_t *server, list_socket_t *deco_sock);
int send_message(list_socket_t *socket, const int code, const char *msg);

list_socket_t *create_node_socket(int fd, socket_type_t type);
int add_in_list_socket(list_socket_t **list, list_socket_t *new);
void delete_list_socket(list_socket_t **list);
int delete_in_list_socket(list_socket_t **list, list_socket_t *ptr);

int start_socket(void);
int bind_socket_tcp(int sfd, unsigned short port);
int start_listen(int sfd);

int setup_catcher(int *stop);

char *get_remote_addr(int socket_fd);
unsigned short get_local_port(int socket_fd);

int count_occ(char *str, char search);
char **strtotab(char *str, char delim);
char *remove_last_char(char *str);
int search_in_list(const char **tab, char *search);
char *absolute_path(char *rel_path);

bool prefix(const char *pre, const char *str);
char *add_slash(list_socket_t *msocket, char *path);

user_t *create_user(char *name, char *pass, char *dirr, user_level_t level);
user_t *search_user(server_t *server, char *name);
void free_user(user_t *user);
void free_list_user(user_t **users);

int check_args(list_socket_t *msocket, char **args, int num_arg, bool logged);
int error_malloc(list_socket_t *msocket, char *msg);

int data_connect(list_socket_t *msocket);

#endif /* !MYFTP_H_ */
