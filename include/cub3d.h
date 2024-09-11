/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:47 by helferna          #+#    #+#             */
/*   Updated: 2024/09/11 19:45:07 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/X.h>
#  include "../mlx_linux/mlx.h"
# endif

# ifdef __APPLE__
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define Q 12
#  define E 14
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
#  include "../mlx_macos/mlx.h"
# endif

# ifdef __linux__
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define Q 113
#  define E 101
#  define F 102
#  define G 103
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
#  define KEYMENUS	65453	
#  define KEYMOR  65451
#  define SPACE 32

# endif

# define M_PI 3.14159265358979323846
# define TILE_SIZE 14
# define FOV 60
# define PLAYER_SPEED 0.04

# define WINWIDTH 800
# define WINHEIGHT 600

typedef struct s_coords
{
	int				x;
	int				y;
}	t_coords;

typedef struct s_vector
{
	double			x;
	double			y;
}	t_vector;

typedef struct s_player
{
	double		speed;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_computes
{
	bool			hit;
	char			dir;
	int				side;
	int				end_wall;
	int				start_wall;
	int				wall_height;
	double			dist_to_wall;
	double			wall_x;
	t_vector		hit_pos;
	t_vector		ray;
	t_coords		map;
	t_coords		step;
	t_vector		delta;
	t_vector		step_size;
}	t_computes;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_controller
{
	bool	mv_fw;
	bool	mv_bw;
	bool	mv_lf;
	bool	mv_rt;
	bool	rt_lf;
	bool	rt_rt;
	bool	game_over;
	bool	mini_map;
	int		speed;
	int		menu;
}	t_controller;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	t_image	*img;
	int		width;
	int		height;
}	t_win;

typedef struct s_map
{
	char			**map;
	int				floor;
	int				ceiling;
	t_image			*no;
	t_image			*so;
	t_image			*we;
	t_image			*ea;
}					t_map;

typedef struct s_cub3d
{
	t_image			img;
	t_map			*map;
	t_player		player;
	int				map_fd;
	t_controller	*ctrl;
	t_win			win;
	t_computes		cols[WINWIDTH];
}	t_cub;

int				exit_all(t_cub *cub);
t_controller	*init_controller(t_cub *cub);
void			player_move(t_player *player, t_controller \
										*controller, char **map);
void			win_fill(t_win *win, int ceiling_color, int floor_color);
void			update_camera_plane(t_player *player);
void			render_2d_map(t_cub *cub, t_map *map, \
									t_win *win, t_player player);
void			render_dimension_3d(t_cub *cub);
void			print_menu(t_cub *data);
void			init_player(t_player *player, t_map *map);
void			put_pixel(t_image *img, int x, int y, int color);
void			draw_square(t_image *img, t_coords cord, int size, int color);
bool			initialization(t_cub *cub);
bool			parse_cub(t_cub *cub, char *path, t_win *win, t_map *map);
void			free_cub(t_cub *cub);
void			ft_free_array(char **array);
size_t			ft_array_len(char **array);
int				rgb_to_hex(int r, int g, int b);
void			raycast(int column, t_map *map, t_player *player, \
													t_computes *computes);
bool			init_mlx(t_cub *cub);
bool			init_win(t_cub *cub);

#endif