NAME = minishell

INCLUDE = include
SRC = src
OBJS = objs

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a
LIBFTI = $(LIBFT)

FT_PRINTF = ft_printf
FT_PRINTFA = $(FT_PRINTF)/libftprintf.a
FT_PRINTFI = $(FT_PRINTF)/include

FILES = main.c		\
	minishell.c	\
	envp_parser.c \
	readline/actions.c	\
	readline/char_utils.c	\
	readline/cursor_position.c	\
	readline/cursor_manager.c	\
	readline/ft_readline.c	\
	readline/handle.c	\
	readline/termios_manager.c	\
	readline/char_list.c	\
	readline/clean_readed.c	\
	readline/display.c	\
	readline/processing.c	\
	readline/resize.c	\
	readline/utils.c	\
	readline/stdin.c	\
	utils/init_int_tab.c \
	utils/check_special_char.c \
	commands/execute_command.c \
	commands/execute_bin.c \
	argv/create_argv.c \
	var_parser.c \
	init_pipes.c \
	whitespace_fixer.c \
	builtins/echo.c \
	builtins/cd.c \
	builtins/pwd.c \
	builtins/unset.c \
	builtins/export.c \
	builtins/export_no_args.c \
	builtins/exit.c \
	builtins/env.c

OFILES = $(FILES:%.c=$(OBJS)/%.o)

FLAGS = -Wall -Wextra -Werror
EXTRA_FLAGS = -g
COMPILATOR = cc

all: $(NAME)

$(NAME): $(LIBFTA) $(FT_PRINTFA) $(OFILES)
	$(COMPILATOR) $(FLAGS) $(OFILES) $(LIBFTA) $(FT_PRINTFA) -o $(NAME) -I $(INCLUDE) -I $(LIBFTI) -I $(FT_PRINTFA) $(EXTRA_FLAGS)

$(LIBFTA):
	@make -C $(LIBFT) bonus > /dev/null

$(FT_PRINTFA):
	@make -C $(FT_PRINTF) bonus > /dev/null

clean:
	@rm -rf $(OFILES)
	@rm -rf $(OBJS)
	@make -C $(LIBFT) clean > /dev/null
	@make -C $(FT_PRINTF) clean > /dev/null

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean > /dev/null
	@make -C $(FT_PRINTF) fclean > /dev/null

$(OBJS)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@$(COMPILATOR) $(FLAGS) $< -c -o $@ -I $(INCLUDE) -I $(LIBFTI) $(EXTRA_FLAGS)

re: fclean all

.PHONY: all clean fclean re
