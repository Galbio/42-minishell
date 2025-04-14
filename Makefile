NAME = minishell

INCLUDE = include
SRC = src
OBJS = objs

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a
LIBFTI = $(LIBFT)

FILES =	main.c									\
	minishell.c									\
	prompt.c									\
	argv/create_argv.c 							\
	argv/argv_utils.c 							\
	argv/var_parser.c 							\
	argv/local_var_handling.c 					\
	argv/add_splitted.c 						\
	argv/parse_cmd_return.c 					\
	argv/braces/expansion.c 					\
	argv/braces/methods.c 						\
	parsers/split_separators.c 					\
	parsers/splitters_utils.c 					\
	parsers/bquotes_handler.c 					\
	parsers/handle_aliases.c 					\
	events/parser.c 							\
	events/handle_replacing.c 					\
	redirections/redirect_stdin.c				\
	redirections/redirect_stdout.c				\
	redirections/add_redir_argv.c				\
	redirections/errors.c 						\
	redirections/heredoc/handle_heredoc.c 		\
	redirections/heredoc/parse_heredocs.c		\
	redirections/heredoc/heredoc_quote_parser.c \
	redirections/heredoc/handle_heredoc_utils.c \
	builtins/echo.c								\
	builtins/cd.c								\
	builtins/change_pwd.c						\
	builtins/pwd.c								\
	builtins/unset.c							\
	builtins/export.c							\
	builtins/export_no_args.c					\
	builtins/exit.c								\
	builtins/env.c								\
	builtins/alias.c							\
	commands/execute_line.c						\
	commands/execute_command.c					\
	commands/execute_command_utils.c			\
	commands/execute_subshell.c					\
	commands/execute_pipes.c					\
	commands/execute_bin.c						\
	commands/execute_subcmd.c					\
	commands/similar_commands.c					\
	commands/commands_errors.c					\
	envp/create_envp_cpy.c						\
	envp/path.c									\
	envp/parser.c								\
	envp/update.c								\
	research/research.c							\
	research/parser.c							\
	research/free.c								\
	utils/init_int_tab.c 						\
	utils/var_names_utils.c 					\
	utils/handle_var_quote.c					\
	utils/cwd_errors.c 							\
	utils/is_only_nb.c 							\
	utils/free_cmd.c 							\
	utils/token_errors.c 						\
	utils/display_errors.c 						\
	utils/get_subcmd.c 							\
	utils/get_cmd_depth.c 						\
	utils/trim_whitespaces.c 					\
	utils/check_special_char.c					\
	regex/checkers/bounds.c						\
	regex/checkers/inside.c						\
	regex/checkers/lengths.c					\
	regex/checkers/first_occurence.c			\
	regex/items/len.c							\
	regex/items/brackets.c						\
	regex/items/manager.c						\
	regex/items/factory.c						\
	regex/items/utils.c							\
	regex/cleaner.c								\
	regex/regex.c								\
	signals/exit_status.c						\
	signals/handler.c


READLINE_FILES =	ft_readline/autocompletion/commands.c		\
					ft_readline/autocompletion/display.c		\
					ft_readline/autocompletion/files_and_dirs.c	\
					ft_readline/autocompletion/research.c		\
					ft_readline/autocompletion/utils.c			\
					ft_readline/autocompletion/variables.c		\
					ft_readline/char/list.c						\
					ft_readline/char/position.c					\
					ft_readline/char/utils.c					\
					ft_readline/clean/backslashes.c				\
					ft_readline/cursor/position/position.c		\
					ft_readline/cursor/position/stdin.c			\
					ft_readline/cursor/position/tty.c			\
					ft_readline/cursor/movements.c				\
					ft_readline/cursor/view.c					\
					ft_readline/edition/delete.c				\
					ft_readline/edition/utils.c					\
					ft_readline/edition/write.c					\
					ft_readline/extra/env/envp.c				\
					ft_readline/extra/env/path.c				\
					ft_readline/extra/erase.c					\
					ft_readline/extra/fd.c						\
					ft_readline/extra/raw_mode.c				\
					ft_readline/extra/size.c					\
					ft_readline/format/checker.c				\
					ft_readline/format/lines_count.c			\
					ft_readline/history/file.c					\
					ft_readline/history/manager.c				\
					ft_readline/history/path.c					\
					ft_readline/history/reader.c				\
					ft_readline/history/state.c					\
					ft_readline/history/writer.c				\
					ft_readline/process/converter.c				\
					ft_readline/process/processor.c				\
					ft_readline/process/handler.c				\
					ft_readline/process/reader.c				\
					ft_readline/process/stash.c					\
					ft_readline/events/default/autocompletion.c	\
					ft_readline/events/default/breakline.c		\
					ft_readline/events/default/clear.c			\
					ft_readline/events/default/delete.c			\
					ft_readline/events/default/five_tilde.c		\
					ft_readline/events/default/history.c		\
					ft_readline/events/default/interrupt.c		\
					ft_readline/events/default/invalid.c		\
					ft_readline/events/default/move.c			\
					ft_readline/events/default/stash_word.c		\
					ft_readline/events/default/stash.c			\
					ft_readline/events/default/swap.c			\
					ft_readline/events/default/teleport.c		\
					ft_readline/events/default_events.c			\
					ft_readline/events/factory.c				\
					ft_readline/exit.c							\
					ft_readline/ft_readline.c					\
					ft_readline/initialization.c				\
					ft_readline/main.c

OFILES = $(FILES:%.c=$(OBJS)/%.o) $(READLINE_FILES:%.c=$(OBJS)/%.o)

HISTORY_SIZE ?= 500

FLAGS = -Wall -Wextra -Werror -D HISTORY_SIZE=$(HISTORY_SIZE)
EXTRA_FLAGS = -g
COMPILATOR = cc

C1=\033[38;2;0;220;206m
C2=\033[38;2;0;202;173m
C3=\033[38;2;0;183;139m
C4=\033[38;2;0;165;106m
C5=\033[38;2;0;148;73m
C6=\033[38;2;0;131;20m
C7=\033[38;2;205;127;50m
CR=\033[0m
FLASH=\033[1m\033[5m
ERASE_AFTER=\033[K
HIDE_CURSOR=\e[?25l
SHOW_CURSOR=\e[?25h
MOVE_UP=\033[F
CLS=\033[2J\033[0;0H

all: header $(NAME)

header:
	@echo "$(CR)$(CLS)========================================================================="
	@echo "$(C1)      ____       __ __ ___        __  ____       _ _____ __         ____\033[0m"
	@sleep .05
	@echo "$(C2)    _/ /\ \     / // /|__ \      /  |/  (_)___  (_) ___// /_  ___  / / /\033[0m"
	@sleep .05
	@echo "$(C3)   / __/ \ \   / // /___/ /_____/ /|_/ / / __ \/ /\__ \/ __ \/ _ \/ / / \033[0m"
	@sleep .05
	@echo "$(C4)  (_  )  / /  /__  __/ __/_____/ /  / / / / / / /___/ / / / /  __/ / /  \033[0m"
	@sleep .05
	@echo "$(C5) /  _/  /_/     /_/ /____/    /_/  /_/_/_/ /_/_//____/_/ /_/\___/_/_(_) \033[0m"
	@sleep .05
	@echo "$(C6) /_/                                                                   \033[0m"
	@echo "=================================================== gakarbou && lroussel."

$(NAME): $(LIBFTA) $(OFILES)
	@echo "\r$(ERASE_AFTER)$(C4)- Files compilation $(C1)done$(C4).$(CR)\n"
	@$(COMPILATOR) $(FLAGS) $(OFILES) $(LIBFTA) -o $(NAME) -I $(INCLUDE) -I $(LIBFTI) $(EXTRA_FLAGS)
	@echo "$(ERASE_AFTER)$(C4)Done compiling executable. You can now run minishell with $(C1)./$(NAME)$(ERASE_AFTER)$(CR)"

$(LIBFTA):
	@echo -n "$(C4)$(FLASH)- Compiling $(C1)libft$(C4)..$(CR)"
	@make -C $(LIBFT) bonus > /dev/null
	@echo "\n$(MOVE_UP)$(ERASE_AFTER)$(C4)- Libft compilation $(C1)done$(C4).$(CR)"

clean:
	@rm -rf $(OFILES)
	@rm -rf $(OBJS)
	@make -C $(LIBFT) clean > /dev/null
	@echo "$(ERASE_AFTER)$(C4)- Cleaning objects files $(C1)done$(C4).$(CR)"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean > /dev/null
	@echo "$(ERASE_AFTER)$(C4)- Cleaning executables files $(C1)done$(C4).$(CR)"

$(OBJS)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@printf "\r$(C4)$(FLASH)- Compiling $(C1)%s$(C4)..$(CR)$(ERASE_AFTER)" "$<"
	@$(COMPILATOR) $(FLAGS) $< -c -o $@ -I $(INCLUDE) -I $(LIBFTI) $(EXTRA_FLAGS)

re: header fclean $(NAME)

valgrind.supp: header
	@echo "$(C6)Hi dude, there's no need for $(C1)that $(C4)here :)"
	@sleep 1
	@echo "We remade readline so $(C1)no leaks are possible $(C4)¯\_(ツ)_/¯"
	@sleep 1
	@echo "\nIf you want a little more info, try to $(C1)$(FLASH)flex Makefile $(CR)$(C4);)$(CR)"

flex : header
	@echo "$(C4)You wanna feel bad about yourself ?... Sure!" ; sleep .8
	@echo "Here's our little $(C1)$(FLASH)\"bonuses\"$(CR)$(C4)\n" ; sleep 1.2
	@echo "$(C7)-$(C4) Backslashes" ; sleep 1 ; echo "$(C7)-$(C4) Full bash regex" ; sleep 1 ; echo "$(C7)-$(C4) Bquotes"
	@sleep 1 ; echo "$(C7)-$(C4) Bash events" ; sleep 1 ; echo "$(C7)-$(C4) Aliases" ; sleep 1
	@echo "$(C7)-$(C4) Our own autocompletion system" ; sleep 1 ; echo "$(C7)-$(C4) Every bash control shortcut"
	@sleep 1 ; echo "$(C7)-$(C4) Local variables" ; sleep 1 ; echo "$(C7)-$(C4) Dynamic Prompt" ; sleep 1
	@echo "$(C7)-$(C4) Funky redirections" ; sleep 1 ; echo "$(C7)-$(C4) Heredoc variable handling" ; sleep 1
	@echo "$(C7)-$(C4) Subshells" ; sleep 1 ; echo "$(C7)-$(C4) A prettier Makefile than yours" ; sleep 1
	@echo "$(C7)-$(C4) Global History" ; sleep 1 ; echo "$(C7)-$(C4) Prompt and standart error" ; sleep 1
	@echo "$(C7)-$(C4) Env builtin arguments" ; sleep 1 ; echo "$(C7)-$(C4) Navigation in deleted directories" ; sleep 1
	@echo "$(C7)-$(C4) Herestrings" ; sleep 1 ; echo "$(C7)-$(C4) Bash variable expansion" ; sleep 1
	@echo "$(C7)-$(C4) Similar commands" ; sleep 1 ; echo "$(C7)-$(C4) Semicolon" ; sleep 1 ; echo "$(C7)-$(C4) Command substitution"
	@sleep 1 ; echo "$(C7)-$(C4) Dynamic variables" ; sleep 1 ; echo "$(C7)-$(C4) Ambigous redirections" ; sleep 1
	@echo "$(C7)-$(C4) Redirection's file name too long" ; sleep 1 ; echo "$(C7)-$(C4) CD options" ; sleep 1
	@echo "$(C7)-$(C4) File permission management" ; sleep 1 ; echo "$(C7)-$(C4) An amazing argv parsing" ; sleep 1
	@echo "$(C7)-$(C4) Perfect envp management" ; sleep 1.2 ; echo "\nAnd most importantly..."
	@sleep 1;
	@echo "$(CR)\n=============="
	@echo "$(C7)~~~$(C4)COMMENTS$(C7)~~~"
	@echo "$(CR)=============="

.PHONY: all clean fclean re
