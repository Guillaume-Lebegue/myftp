/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** myftp
*/

#ifndef MYFTP_H_
#define MYFTP_H_

static const int SUCCESS = 0;
static const int FAILURE = 84;

static const int QUEUE_LENGTH = 10;

typedef enum {
    SERVER,
    CLIENT
} socket_type_t;

typedef struct list_socket_s{
    struct list_socket_s *next;
    char *dirr_path;
    int fd;
    socket_type_t type;
} list_socket_t;

typedef struct {
    list_socket_t *list_socket;
    char *default_path;
} server_t;

int start_server(short port, char *default_path);
int new_connect(server_t *server, list_socket_t *ssocket);

void server_log(char *msg);
int set_fd_set(int max, fd_set *set, list_socket_t *list, socket_type_t type);

list_socket_t *create_node_socket(int fd, socket_type_t type);
list_socket_t *search_node_socket(list_socket_t *list, int fd);
int add_in_list_socket(list_socket_t **list, list_socket_t *new);
void delete_list_socket(list_socket_t **list);
int delete_in_list_socket(list_socket_t **list, list_socket_t *ptr);

int start_socket(void);
int bind_socket_tcp(int sfd, unsigned short port);
int start_listen(int sfd);

#endif /* !MYFTP_H_ */
