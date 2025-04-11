NAME = minishell

INCLUDE = include
SRC = src
OBJS = objs

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a
LIBFTI = $(LIBFT)

FILES =	main.c		\
	minishell.c	\
	argv/create_argv.c \
	argv/argv_utils.c \
	argv/var_parser.c \
	argv/local_var_handling.c \
	argv/add_splitted.c \
	argv/parse_cmd_return.c \
	parsers/split_separators.c \
	parsers/splitters_utils.c \
	parsers/bquotes_handler.c \
	parsers/handle_aliases.c \
	redirections/redirect_stdin.c \
	redirections/redirect_stdout.c \
	redirections/add_redir_argv.c \
	redirections/heredoc/handle_heredoc.c \
	redirections/heredoc/parse_heredocs.c \
	redirections/heredoc/heredoc_quote_parser.c \
	redirections/heredoc/handle_heredoc_utils.c \
	builtins/echo.c \
	builtins/cd.c \
	builtins/change_pwd.c \
	builtins/pwd.c \
	builtins/unset.c \
	builtins/export.c \
	builtins/export_no_args.c \
	builtins/exit.c \
	builtins/env.c \
	builtins/alias.c \
	commands/execute_line.c \
	commands/execute_command.c \
	commands/execute_command_utils.c \
	commands/execute_subshell.c \
	commands/execute_pipes.c \
	commands/execute_bin.c \
	commands/execute_subcmd.c \
	envp/parser.c \
	envp/create_envp_cpy.c \
	research/research.c		\
	research/parser.c		\
	research/free.c			\
	utils/init_int_tab.c \
	utils/var_names_utils.c \
	utils/cwd_errors.c \
	utils/is_only_nb.c \
	utils/free_cmd.c \
	utils/token_errors.c \
	utils/get_subcmd.c \
	utils/get_cmd_depth.c \
	utils/trim_whitespaces.c \
	utils/check_special_char.c	\
	regex/checkers/bounds.c		\
	regex/checkers/inside.c		\
	regex/checkers/lengths.c		\
	regex/checkers/first_occurence.c	\
	regex/items/len.c	\
	regex/items/brackets.c	\
	regex/items/manager.c		\
	regex/items/factory.c		\
	regex/items/utils.c		\
	regex/cleaner.c			\
	regex/regex.c	\
	signals/exit_status.c	\
	signals/handler.c


READLINE_FILES =	ft_readline/char/list.c					\
					ft_readline/char/position.c				\
					ft_readline/char/utils.c				\
					ft_readline/clean/backslashes.c			\
					ft_readline/cursor/position/position.c	\
					ft_readline/cursor/position/stdin.c		\
					ft_readline/cursor/position/tty.c		\
					ft_readline/cursor/movements.c			\
					ft_readline/cursor/view.c				\
					ft_readline/edition/delete.c			\
					ft_readline/edition/utils.c				\
					ft_readline/edition/write.c				\
					ft_readline/extra/erase.c				\
					ft_readline/extra/fd.c					\
					ft_readline/extra/raw_mode.c			\
					ft_readline/extra/size.c				\
					ft_readline/format/checker.c			\
					ft_readline/format/lines_count.c		\
					ft_readline/history/file.c				\
					ft_readline/history/manager.c			\
					ft_readline/history/path.c				\
					ft_readline/history/reader.c			\
					ft_readline/history/state.c				\
					ft_readline/history/writer.c			\
					ft_readline/process/converter.c			\
					ft_readline/process/processor.c			\
					ft_readline/process/handler.c			\
					ft_readline/process/reader.c			\
					ft_readline/process/stash.c				\
					ft_readline/events/default/breakline.c	\
					ft_readline/events/default/clear.c		\
					ft_readline/events/default/delete.c		\
					ft_readline/events/default/five_tilde.c	\
					ft_readline/events/default/history.c	\
					ft_readline/events/default/interrupt.c	\
					ft_readline/events/default/invalid.c	\
					ft_readline/events/default/move.c		\
					ft_readline/events/default/stash_word.c	\
					ft_readline/events/default/stash.c		\
					ft_readline/events/default/swap.c		\
					ft_readline/events/default/teleport.c	\
					ft_readline/events/default_events.c		\
					ft_readline/events/factory.c			\
					ft_readline/exit.c						\
					ft_readline/ft_readline.c				\
					ft_readline/initialization.c			\
					ft_readline/main.c

OFILES = $(FILES:%.c=$(OBJS)/%.o) $(READLINE_FILES:%.c=$(OBJS)/%.o)

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
