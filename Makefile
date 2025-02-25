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
	utils/get_next_line.c	\
	utils/ft_realloc.c	\
	utils/ft_is_quote.c	\
	utils/ft_is_whitespace.c \
	utils/ft_securejoin.c \
	utils/ft_securelen.c \
	utils/init_int_tab.c \
	utils/ft_strcdup.c \
	builtins/cd.c \
	builtins/echo.c \
	builtins/unset.c \
	builtins/pwd.c \
	builtins/exit.c \
	builtins/export.c \
	commands/execute_command.c \
	build_in.c \
	commands/create_argv.c \
	parse_commands.c \
	var_parser.c

OFILES = $(FILES:%.c=$(OBJS)/%.o)

FLAGS = -Wall -Wextra -Werror
EXTRA_FLAGS = -g #-l history -l readline -lncurses
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
