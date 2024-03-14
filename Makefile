# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 17:25:02 by helferna          #+#    #+#              #
#    Updated: 2024/03/12 13:30:55 by helferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = cub3d
OS    = $(shell uname)
CC    = @gcc
FLAGS = -Wall -Wextra -g -fsanitize=address
LFT   = libft/libft.a
INC   = -I./libft -I.mlx -I./mlx_macos -I./include
SRC   = src/main.c src/map/read_map.c src/utils/utils.c src/player_moves/player_moves.c
OBJ   = $(patsubst src/%.c, obj/%.o, $(SRC))

ifeq ($(OS), Darwin)
	MLX = ./mlx_macos/libmlx.a
	INC_MLX = mlx_macos
   	LIB = -L./libft -lft -L./mlx_macos -lmlx -framework OpenGL -framework AppKit
else
	MLX = /minilibx-linux/libmlx.a
	INC_MLX = minilibx-linux
	LIB = -L./libft -lft -L./minilibx-linux -lmlx -lXext -lX11
endif

# COLORS
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

all: $(MLX) $(LFT) obj $(NAME)

$(NAME): $(OBJ)
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling $(NAME)..."
	$(CC) $(FLAGS) -o $@ $^ $(LIB)
	@echo "[" "$(GREEN)OK$(RESET)" "] | $(NAME) ready!"

$(MLX):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling minilibx..."
	@make -sC $(INC_MLX) > /dev/null 2>&1
	@echo "[" "$(GREEN)OK$(RESET)" "] | Minilibx ready!"

$(LFT):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling libft..."
	@make -sC libft
	@echo "[" "$(GREEN)OK$(RESET)" "] | Libft ready!"

obj:
	@mkdir -p obj

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing object files...$(RESET)"
	@make -sC libft clean
	@make -sC $(INC_MLX) clean > /dev/null
	@rm -rf $(OBJ) obj
	@echo "[" "$(GREEN)OK$(RESET)" "] | Object files removed."

fclean: clean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing binary files...$(RESET)"
	@make -sC libft fclean
	@rm -rf $(NAME)
	@echo "[" "$(GREEN)OK$(RESET)" "] | Binary file removed."

re: fclean all

.PHONY: all