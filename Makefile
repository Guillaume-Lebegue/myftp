##
## EPITECH PROJECT, 2019
## standard Makefile
## File description:
## Makefile
##

SRC	=	src/main.c				\
		src/base_server.c		\
		src/list_socket_utils.c	\
		src/socket_utils.c		\
		src/server_utils.c		\
		src/new_connect.c

OBJ	=	$(SRC:.c=.o)

HEADER_PATH	=	include/

CC	=	@gcc

CFLAGS	=	-I $(HEADER_PATH) -Wall -Werror

NAME	=	myftp

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo compile $(NAME)
	$(CC) -o $(NAME) $(OBJ)

clean:
	@echo Clean .o, $(NAME)
	@rm -rf $(OBJ)

fclean: clean
	@echo Clean $(NAME)
	@rm -rf $(NAME)

re: fclean all
