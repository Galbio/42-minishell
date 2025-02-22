NAME = minishell

CC = cc -g

all : $(NAME)
	$(CC) src/*.c -I include/
