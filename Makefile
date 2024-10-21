# Name

NAME = minishell

# Text Colors and Emojis

RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m
CHECK = \xE2\x9C\x94
BROOM = \xF0\x9F\xA7\xB9

# Compilers

CFLAGS = -Wall -Wextra -Werror -g3
CC = gcc

# Sources

SRC =	srcs/main.c \
# Objects

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBRARIES) $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(CHECK)Compiled $(NAME) Successfully$(CHECK)$(RESET)"

%.o : %.c srcs/../includes/minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(RED)$(BROOM)Cleaned $(NAME) Objects$(BROOM)$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(BROOM)Cleaned $(NAME) Executable$(BROOM)$(RESET)"

re: fclean all

.PHONY: all clean fclean re