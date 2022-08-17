NAME = philo
LIBFT = libft/libft.a
LIB_F = libft
CC = gcc
CFLAGS = -Wall -Werror -Wextra
TFLAG = -lpthread

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(TFLAG) $(LIBFT) *.c -o $(NAME)

$(LIBFT): $(LIB_F)
	make -C $(LIB_F)

clean:
	make clean -C $(LIB_F)

fclean: clean
	make fclean -C $(LIB_F)
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
