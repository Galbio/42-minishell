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
	ft_readline/history/manager.c	\
	ft_readline/history/reader.c	\
	ft_readline/history/writer.c	\
	ft_readline/history/file.c	\
	ft_readline/history/path.c	\
	ft_readline/history/state.c	\
	ft_readline/special_key/move.c	\
	ft_readline/special_key/history.c	\
	ft_readline/special_key/breakline.c	\
	ft_readline/special_key/delete.c	\
	ft_readline/special_key/factory.c	\
	ft_readline/special_key/interrupt.c	\
	ft_readline/special_key/invalid.c	\
	ft_readline/special_key/teleport.c	\
	ft_readline/special_key/stash.c	\
	ft_readline/special_key/stash_word.c	\
	ft_readline/special_key/clear.c	\
	ft_readline/special_key/swap.c	\
	ft_readline/special_key/five_tilde.c	\
	ft_readline/char_utils.c	\
	ft_readline/cursor_position.c	\
	ft_readline/cursor_manager.c	\
	ft_readline/cursor_view.c	\
	ft_readline/ft_readline.c	\
	ft_readline/handle.c	\
	ft_readline/termios_manager.c	\
	ft_readline/char_list.c	\
	ft_readline/clean_readed.c	\
	ft_readline/edition/write.c	\
	ft_readline/edition/delete.c	\
	ft_readline/edition/utils.c	\
	ft_readline/processing.c	\
	ft_readline/size.c	\
	ft_readline/format.c	\
	ft_readline/stdin.c	\
	ft_readline/ft_readline_core.c	\
	ft_readline/exit.c		\
	ft_readline/char_position.c	\
	ft_readline/lines.c		\
	ft_readline/stash.c	\
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
