NAME = minishell

INCLUDE = include
SRC = src
OBJS = objs

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a
LIBFTI = $(LIBFT)

FILES = main.c		\
	minishell.c	\
	bquotes_handler.c \
	signals.c		\
	split_separators.c \
	argv/create_argv.c \
	argv/argv_utils.c \
	argv/var_parser.c \
	argv/add_splitted.c \
	argv/parse_cmd_return.c \
	redirections/redirect_stdin.c \
	redirections/redirect_stdout.c \
	redirections/add_redir_argv.c \
	builtins/echo.c \
	builtins/cd.c \
	builtins/change_pwd.c \
	builtins/pwd.c \
	builtins/unset.c \
	builtins/export.c \
	builtins/export_no_args.c \
	builtins/exit.c \
	builtins/env.c \
	commands/execute_line.c \
	commands/execute_command.c \
	commands/execute_command_utils.c \
	commands/execute_subshell.c \
	commands/execute_pipes.c \
	commands/execute_bin.c \
	envp/parser.c \
	envp/create_envp_cpy.c \
	readline/history/manager.c	\
	readline/history/reader.c	\
	readline/history/writer.c	\
	readline/history/file.c	\
	readline/history/path.c	\
	readline/history/state.c	\
	readline/special_key/move.c	\
	readline/special_key/history.c	\
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
	readline/cursor_view.c	\
	readline/ft_readline.c	\
	readline/handle.c	\
	readline/termios_manager.c	\
	readline/char_list.c	\
	readline/clean_readed.c	\
	readline/edition/write.c	\
	readline/edition/delete.c	\
	readline/edition/utils.c	\
	readline/processing.c	\
	readline/size.c	\
	readline/format.c	\
	readline/stdin.c	\
	readline/ft_readline_core.c	\
	readline/exit.c		\
	readline/char_position.c	\
	readline/lines.c		\
	readline/stash.c	\
	utils/init_int_tab.c \
	utils/var_names_utils.c \
	utils/is_only_nb.c \
	utils/free_cmd.c \
	utils/trim_whitespaces.c \
	utils/check_special_char.c

OFILES = $(FILES:%.c=$(OBJS)/%.o)

HISTORY_SIZE ?= 500

FLAGS = -Wall -Wextra -Werror -D HISTORY_SIZE=$(HISTORY_SIZE)
EXTRA_FLAGS = -g
COMPILATOR = cc

all: $(NAME)

$(NAME): $(LIBFTA) $(OFILES)
	$(COMPILATOR) $(FLAGS) $(OFILES) $(LIBFTA) -o $(NAME) -I $(INCLUDE) -I $(LIBFTI) $(EXTRA_FLAGS)

$(LIBFTA):
	@make -C $(LIBFT) bonus > /dev/null

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
