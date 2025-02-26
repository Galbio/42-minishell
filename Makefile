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
	readline/actions.c	\
	readline/char_utils.c	\
	readline/cursor_position.c	\
	readline/ft_readline.c	\
	readline/termios_manager.c	\
	readline/char_list.c	\
	readline/clean_readed.c	\
	readline/display.c	\
	readline/processing.c	\
	readline/utils.c	\
	utils/init_int_tab.c \
	commands/execute_command.c \
	argv/create_argv.c \
	build_in.c \
	parse_commands.c \
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
