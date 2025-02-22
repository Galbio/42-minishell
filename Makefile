NAME = minishell

INCLUDE = include
SRC = src
OBJS = objs

FILES = main.c
OFILES = $(FILES:%.c=$(OBJS)/%.o)

FLAGS = -Wall -Wextra -Werror -g
COMPILATOR = cc

all: $(NAME)

$(NAME): $(OFILES)
	$(COMPILATOR) $(FLAGS) $(OFILES) -o $(NAME) -I $(INCLUDE)

clean:
	@rm -rf $(OFILES)
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

$(OBJS)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@$(COMPILATOR) $(FLAGS) $< -c -o $@ -I $(INCLUDE)

re: fclean all

.PHONY: all clean fclean re
