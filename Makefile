NAME = philo
LIBFT = libft/libft.a
LIB_F = libft
CC = gcc
CFLAGS = -Wall -Werror -Wextra
TFLAG = -lpthread
SRCS = philosophers.c utils.c loop.c

ARG = 30 200 100 50 

all: $(NAME)

tey : run a a1 a2 a3

a : test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test

a1 : test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test

a2 : test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test

a3 : test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test
	@make test

test: run
	@gcc test.c -o test.exe
	@./test.exe test.txt "$(ARG)"

run: all
	@./philo $(ARG) | cat >> test.txt

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(TFLAG) $(LIBFT) $(SRCS) -o $(NAME)

$(LIBFT): $(LIB_F)
	make -C $(LIB_F)

clean:
	make clean -C $(LIB_F)

fclean: clean
	make fclean -C $(LIB_F)
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
