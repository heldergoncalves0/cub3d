/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:47 by helferna          #+#    #+#             */
/*   Updated: 2024/03/26 14:29:41 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include "../libft/libft.h"

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/X.h>
# endif

# ifdef __APPLE__
# include "../mlx_macos/mlx.h"
#  define ESCAPE 53
#  define W 13
#  define S 1
#  define A 0
#  define D 2
#  define LEFT 123
#  define RIGHT 124
#  define UP 126
#  define DOWN 125
# endif

# ifdef __linux__
# include "../minilibx-linux/mlx.h"
#  define ESCAPE 65307
#  define W 119
#  define S 115
#  define A 97
#  define D 100
#  define LEFT 65361
#  define RIGHT 65363
#  define UP 65362
#  define DOWN 65364
# endif

#define PI 3.1428
#define TILE_SIZE 32
#define FOV 60
#define PLAYER_SPEED 2

typedef struct	s_ray{
	float	angle;
	int		distance;
}	t_ray;

typedef struct s_player{
	int		pixel_x;
	int		pixel_y;
	int		p_x;
	int		p_y;
	double	angle;
	int		u_d;
	int		r_l;
}	t_player;

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct    s_cub3d{
	t_image		img;
	t_ray		ray;
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	int			map_fd;
}	t_cub;

t_cub	*cub(void);
int		close_window(t_cub	*cub);
char	**read_map(t_cub	*cub);
void	move_player_up(t_cub *cub);
void	shoot_rays(t_cub *cub);
void	render_wall(t_cub *cub, int ray);
float	nor_angle(float angle);
void	img_pix_put(t_image *img, int x, int y, int color);
