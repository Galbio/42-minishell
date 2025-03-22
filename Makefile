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
	bquotes_handler.c \
	init_pipes.c \
	signals.c		\
	split_semicolon.c \
	argv/create_argv.c \
	argv/argv_utils.c \
	argv/var_parser.c \
	argv/add_splitted.c \
	argv/parse_cmd_return.c \
	builtins/echo.c \
	builtins/cd.c \
	builtins/pwd.c \
	builtins/unset.c \
	builtins/export.c \
	builtins/export_no_args.c \
	builtins/exit.c \
	builtins/env.c \
	commands/execute_command.c \
	commands/execute_command_utils.c \
	commands/execute_pipes.c \
	commands/execute_bin.c \
	readline/special_key/arrow.c	\
	readline/special_key/breakline.c	\
	readline/special_key/delete.c	\
	readline/special_key/factory.c	\
	readline/special_key/interrupt.c	\
	readline/special_key/invalid.c	\
	readline/special_key/teleport.c	\
	readline/special_key/stash.c	\
	readline/special_key/stash_word.c	\
	readline/special_key/clear.c	\
	readline/special_key/swap.c	\
	readline/special_key/five_tilde.c	\
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
	readline/size.c	\
	readline/utils.c	\
	readline/stdin.c	\
	readline/ft_readline_core.c	\
	readline/exit.c		\
	readline/char_position.c	\
	readline/lines.c		\
	readline/stash.c	\
	utils/init_int_tab.c \
	utils/go_to_var_end.c \
	utils/free_envp.c \
	utils/trim_whitespaces.c \
	utils/is_backslashed.c \
	utils/check_special_char.c

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
