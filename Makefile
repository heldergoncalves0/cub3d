# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 17:25:02 by helferna          #+#    #+#              #
#    Updated: 2024/09/10 16:21:52 by helferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = cub3D
OS    = $(shell uname)
CC    = @cc
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
LFT   = libft/libft.a
INC   = -I./libft -I.mlx -I./mlx_macos -I./include
SRC   = src/main.c src/bye.c src/controller.c src/mlx_helper.c src/player_move.c \
        src/player.c src/render_2d.c src/render_3d.c src/init.c src/parsing/parser.c \
		src/parsing/parse_configs.c src/parsing/parse_map.c src/parsing/parse_map_utils.c \
		src/parsing/parse_configs_utils.c src/parsing/parse_configs_textures.c \
		src/parsing/parse_configs_line.c src/parsing/parse_configs_colors.c \
		src/raycasting/raycast.c src/raycasting/helpers.c 
OBJ   = $(patsubst src/%.c, obj/%.o, $(SRC))

ifeq ($(OS), Darwin)
	MLX = ./mlx_macos/libmlx.a
	INC_MLX = mlx_macos
   	LIB = -L./libft -lft -L./mlx_macos -lmlx -framework OpenGL -framework AppKit
else
	MLX = /mlx_linux/libmlx.a
	INC_MLX = mlx_linux
	LIB = -L./libft -lft -L./mlx_linux -lmlx -lXext -lX11
endif

# COLORS
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

all: $(MLX) $(LFT) obj $(NAME)

$(NAME): $(OBJ)
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling $(NAME)..."
	$(CC) $(FLAGS) -o $@ $^ $(LIB) -lm
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