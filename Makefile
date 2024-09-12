# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 11:21:41 by helferna          #+#    #+#              #
#    Updated: 2024/09/12 11:21:43 by helferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = cub3D

# Compilador e flags de compilação
CC = cc
CFLAGS = -Werror -Wall -Wextra #-fsanitize=address -g

# Bibliotecas e flags de ligação
LFLAGS = -lm -lbsd

# Diretório da MiniLibX
MLXDIR = mlx_linux

# Diretório da Libft
LIBFTDIR = libft

# Detecção do sistema operacional
UNAME := $(shell uname -s)
ifeq ($(UNAME), Linux)
    MLX_NAME = libmlx_Linux.a
    LFLAGS += -L$(MLXDIR) -lmlx_Linux -lXext -lX11
endif

# Diretórios e arquivos fonte
OBJDIR = obj
SRCDIR = src/
INCDIR = include

# Lista de arquivos fonte
#SRCS = $(SRCDIR)/plot.c $(SRCDIR)/vec3.c $(SRCDIR)/safe_functions.c

# Lista de arquivos fonte usando wildcard para pegar todos os .c em src
SRCS   = src/main.c src/menu.c src/bye.c src/controller.c src/mlx_helper.c src/player_move.c \
        src/player.c src/render_2d.c src/render_3d.c src/init.c src/parsing/parser.c \
		src/parsing/parse_configs.c src/parsing/parse_map.c src/parsing/parse_map_utils.c \
		src/parsing/parse_configs_utils.c src/parsing/parse_configs_textures.c \
		src/parsing/parse_configs_line.c src/parsing/parse_configs_colors.c \
		src/raycasting/raycast.c src/raycasting/helpers.c

# Lista de objetos a serem gerados
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Diretórios adicionais de includes e bibliotecas
INCLUDES = -I$(MLXDIR) -I$(INCDIR) -I$(LIBFTDIR)

# Cores para indicar fases do processo
COLOR_RESET = \033[0m
COLOR_INFO = \033[38;5;46m
COLOR_SUCCESS = \033[38;5;82m
COLOR_CLEAN = \033[38;5;208m

# Alvo padrão: compilar o executável
all: $(NAME)
	@echo "$(COLOR_SUCCESS)Compilação concluída com sucesso!$(COLOR_RESET)"
	@echo "$(COLOR_INFO)Executável: ./$(NAME)$(COLOR_RESET)"

# Regra para compilar o executável
$(NAME): $(OBJS) $(LIBFTDIR)/libft.a
	@echo "$(COLOR_INFO)Compilando $(NAME)...$(COLOR_RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -L$(LIBFTDIR) -lft -o $(NAME)

# Regra para compilar arquivos fonte em objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "$(COLOR_INFO)Compilando $<...$(COLOR_RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Criação do diretório de objetos
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(COLOR_INFO)Criando diretório de objetos: $(OBJDIR)$(COLOR_RESET)"

# Regra para compilar a libft
$(LIBFTDIR)/libft.a:
	@echo "$(COLOR_INFO)Compilando libft...$(COLOR_RESET)"
	$(MAKE) -C $(LIBFTDIR)

# Alvo de limpeza: remove arquivos objeto
clean:
	@$(RM) -r $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean

# Alvo de limpeza completa: remove arquivos temporários, objetos e o executável
fclean: clean
	@echo "$(COLOR_CLEAN)Limpando tudo...$(COLOR_RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

# Alvo de reconstrução completa: limpa tudo e reconstrói o executável
re: fclean all

# Indica que estes alvos não correspondem a arquivos reais
.PHONY: all clean fclean re