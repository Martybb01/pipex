NAME = pipex
CC = cc
CFLAGS = -Wextra -Werror -Wall -g
RM = rm -f

LIBFT = libft_extended/libft.a

SRC = prova.c \
error.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): lib_comp comp

lib_comp:
	make -C libft_extended/

comp:
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	make clean -C libft_extended/
	$(RM) $(NAME)

re: fclean all
