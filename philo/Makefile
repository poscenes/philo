NAME = philo

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC = src/forks.c src/init.c \
	src/main.c src/philo.c src/utils.c \

INCLUDES = include/philo.h

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(FLAGS) $(OBJ) -lpthread -o $(NAME)

%.o: %.c $(INCLUDES)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all
