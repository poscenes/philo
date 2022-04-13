NAME = philo_bonus

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC = src/init.c src/lifecycle.c \
	src/utils.c src/philosophers.c

INCLUDES = include/philo_bonus.h

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
