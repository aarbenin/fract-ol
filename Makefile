GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

NAME = fractol

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = ./libft
MLX_PATH = ./minilibx

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/color_schemes/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_PATH)/libft.a
MLX = $(MLX_PATH)/libmlx.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LFLAGS = -L$(MLX_PATH) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
endif
ifeq ($(UNAME_S),Darwin)
	LFLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME):  $(LIBFT) $(MLX) $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) -L$(LIBFT_PATH) -lft $(LFLAGS)
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/*.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -I $(LIBFT_PATH) -I $(MLX_PATH) -c $< -o $@
	@echo "$(GREEN)Compiled: $< $(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	@$(MAKE) -C $(MLX_PATH)

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@if [ -d "$(OBJ_DIR)" ]; then rm -r $(OBJ_DIR) && echo "$(NAME): $(RED)$(OBJ_DIR) was deleted$(RESET)"; fi

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
