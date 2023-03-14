NAME = philo
R_NAME = philo_race

CC = gcc
CFLAGS = -Wall -Wextra -Werror

TFLAG = -lpthread
SRCS = main.c utils.c init.c philo.c

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(TFLAG) $(SRCS) -o $(NAME)

race:
	$(CC) $(CFLAGS) -fsanitize=thread $(TFLAG) $(SRCS) -o $(R_NAME)

clean :
	rm -rf $(NAME) $(R_NAME)

fclean :
	rm -rf $(NAME) $(R_NAME)

re : fclean all

.PHONY: clean fclean re all
