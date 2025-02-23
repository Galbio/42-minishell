NAME = minishell

INCLUDE = include
SRC = src
OBJS = objs

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a
LIBFTI = $(LIBFT)

FILES = main.c		\
	minishell.c	\
	envp_parser.c \
	quote_parser.c \
	utils/ft_readline.c	\
	utils/clean_readed.c	\
	utils/ft_realloc.c	\
	utils/get_next_line.c	\
	utils/ft_is_quote.c	\
	utils/ft_is_whitespace.c \
	utils/ft_securejoin.c \
	utils/ft_securelen.c \
	commands/execute_command.c \
	commands/create_argv.c \
	var_parser.c

OFILES = $(FILES:%.c=$(OBJS)/%.o)

FLAGS = -Wall -Wextra -Werror
EXTRA_FLAGS = -g
COMPILATOR = cc

all: $(NAME)

$(NAME): $(LIBFTA) $(OFILES)
	$(COMPILATOR) $(FLAGS) $(OFILES) $(LIBFTA) -o $(NAME) -I $(INCLUDE) -I $(LIBFTI) $(EXTRA_FLAGS)

$(LIBFTA):
	@make -C libft/ bonus > /dev/null

clean:
	@rm -rf $(OFILES)
	@rm -rf $(OBJS)
	@make -C $(LIBFT) clean > /dev/null

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean > /dev/null

$(OBJS)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@$(COMPILATOR) $(FLAGS) $< -c -o $@ -I $(INCLUDE) -I $(LIBFTI) $(EXTRA_FLAGS)

re: fclean all

.PHONY: all clean fclean re
