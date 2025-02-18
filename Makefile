# Name
.SILENT:
NAME = minishell

# Text Colors and Emojis
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m
CHECK = \xE2\x9C\x94
BROOM = \xF0\x9F\xA7\xB9

# Libft
LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a
INCLUDES = -I ./includes -I $(LIBFT_PATH)
INCLUDES = -I $(LIBFT_PATH)

# Compilers
CFLAGS = -Wall -Wextra -Werror -g3
CC = gcc
LDFLAGS = -lreadline

SRC_DIR = src
OBJ_DIR = obj

# Sources
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/tokenizing/tokenizing.c \
		$(SRC_DIR)/tokenizing/utils.c \
		$(SRC_DIR)/tokenizing/token_utils.c \
		$(SRC_DIR)/builtins/cd.c \
		$(SRC_DIR)/builtins/echo.c \
		$(SRC_DIR)/builtins/utils.c \
		$(SRC_DIR)/builtins/env.c \
		$(SRC_DIR)/builtins/exit.c \
		$(SRC_DIR)/builtins/pwd.c \
		$(SRC_DIR)/builtins/export.c \
		$(SRC_DIR)/builtins/unset.c \
		$(SRC_DIR)/builtins/export_utils.c \
		$(SRC_DIR)/clean_functions/clean_message.c \
		$(SRC_DIR)/clean_functions/tree_cleanup.c \
		$(SRC_DIR)/clean_functions/env_cleanup.c \
		$(SRC_DIR)/error_functions/error.c \
		$(SRC_DIR)/exec/utils.c \
		$(SRC_DIR)/exec/builtins_exe.c \
		$(SRC_DIR)/parser/parsing.c \
		$(SRC_DIR)/parser/redirections.c \
		$(SRC_DIR)/parser/redir_utils.c \
		$(SRC_DIR)/error_functions/freeing.c \
		$(SRC_DIR)/parser/expand.c \
		$(SRC_DIR)/parser/pipes.c \
		$(SRC_DIR)/parser/parse_utils.c \
		$(SRC_DIR)/execution/exec.c


OBJS = $(SRC:.c=.o)


all: $(LIBFT) $(OBJS) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "$(GREEN)$(CHECK) Compiled $(LIBFT_PATH) Successfully $(CHECK)$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(GREEN)$(CHECK) Compiled $(NAME) Successfully $(CHECK)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(OBJS)
	@rm -rf $(LIBFT)
	@echo "$(RED)$(BROOM) Cleaned Libft Objects $(BROOM)$(RESET)"
	@echo "$(RED)$(BROOM) Cleaned $(NAME) Objects $(BROOM)$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(BROOM) Cleaned $(NAME) Executable $(BROOM)$(RESET)"

re: fclean all

.PHONY: all clean fclean re
