# Name

NAME = minishell

# Text Colors and Emojis

RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m
CHECK = \xE2\x9C\x94
BROOM = \xF0\x9F\xA7\xB9

#Libft

LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a
INCLUDES = -I $(LIBFT_PATH)

# Compilers

CFLAGS = -Wall -Wextra -Werror -g3
CC = gcc
LDFLAGS = -lreadline

# Sources

SRC =	src/main.c \
		src/tokenizing/tokenizing.c \
		src/tokenizing/utils.c \
		src/tokenizing/token_utils.c \
		src/execution/exec.c \
		src/parser/parsing.c \
		src/parser/parsing_utils.c \
		src/expansion/expand_env.c

# Objects

OBJ = $(SRC:.c=.o)

all:  $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@echo "$(GREEN)$(CHECK)Compiled Libft Successfully$(CHECK)$(RESET)"

$(NAME): $(LIBRARIES) $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(CHECK)Compiled $(NAME) Successfully$(CHECK)$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -f $(OBJ)
	@echo "$(RED)$(BROOM)Cleaned Libft Objects$(BROOM)$(RESET)"
	@echo "$(RED)$(BROOM)Cleaned $(NAME) Objects$(BROOM)$(RESET)"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)$(BROOM)Cleaned Libft Executable$(BROOM)$(RESET)"
	@echo "$(RED)$(BROOM)Cleaned $(NAME) Executable$(BROOM)$(RESET)"

re: fclean all

.PHONY: all clean fclean re