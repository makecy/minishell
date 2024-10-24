# Name
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
INCLUDES = -I $(LIBFT_PATH) -I includes

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@echo "$(GREEN)$(CHECK) Compiled Libft Successfully $(CHECK) $(RESET)"

# Compilers
CFLAGS = -Wall -Wextra -Werror -g3
CC = gcc

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Sources
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/tokenizing/tokenizing.c \
		$(SRC_DIR)/tokenizing/utils.c \
		$(SRC_DIR)/tokenizing/token_utils.c

# Objects
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))  # Corrected line

# All
all: $(OBJ_DIR) $(NAME) $(LIBFT)

# Create object directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/tokenizing:
	mkdir -p $(OBJ_DIR)/tokenizing

# Build Executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(CHECK) Compiled $(NAME) Successfully $(CHECK) $(RESET)"

# Rule for .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(OBJ_DIR)/tokenizing
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	@make -C $(LIBFT_PATH) clean
	@rm -f $(OBJ)
	@echo "$(RED)$(BROOM) Cleaned Libft Objects $(BROOM) $(RESET)"
	@echo "$(RED)$(BROOM) Cleaned $(NAME) Objects $(BROOM) $(RESET)"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)$(BROOM) Cleaned Libft Executable $(BROOM) $(RESET)"
	@echo "$(RED)$(BROOM) Cleaned $(NAME) Executable $(BROOM) $(RESET)"

re: fclean all

.PHONY: all clean fclean re

