/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:11 by helferna          #+#    #+#             */
/*   Updated: 2024/06/04 02:12:33 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ------------------  Shooting rays  ------------------ //

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	unit_circle(float angle, char axis)
{
	if (axis == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else
	{
		if (angle > PI / 2 && angle < 3 * PI / 2)
			return (1);
	}
	return (0);
}

float	get_h_inter(t_cub *cub, float angle)
{
	float	y_step;
	float	x_step;
	float	h_y;
	int		pixel;
	float	h_x;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = (floor(cub->player.p_y / TILE_SIZE) * TILE_SIZE);
	h_x = cub->player.p_x + ((h_y - cub->player.p_x) / tan(angle));
	pixel = inter_check(angle, &h_y, &y_step, 1);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	//CHECK WALL HIT
	return (sqrt(pow(h_x - cub->player.p_x, 2) + pow(h_y - cub->player.p_y, 2)));
}

float	get_v_inter(t_cub *cub, float angle)
{
	float	x_step;
	float	y_step;
	float	v_x;
	int 	pixel;
	float	v_y;

	x_step = TILE_SIZE / tan(angle);
	y_step = TILE_SIZE;
	v_x = (floor(cub->player.p_x / TILE_SIZE) * TILE_SIZE);
	v_y = cub->player.p_y + ((v_x - cub->player.p_y) / tan(angle));
	pixel = inter_check(angle, &v_x, &x_step, 0);
	// if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0))
	// 	y_step *= -1;
	//CHECK WALL HIT
	return (sqrt(pow(v_x - cub->player.p_x, 2) + pow(v_y - cub->player.p_y, 2)));
}

void	shoot_rays(t_cub *cub)
{
	int		ray;
	float	h_inter;
	float	v_inter;

	h_inter = 0;
	v_inter = 0;
	ray = 0;
	cub->ray.angle = cub->player.angle - FOV / 2;
	while (ray < 1024)
	{
		h_inter = get_h_inter(cub, cub->ray.angle);
		v_inter = get_v_inter(cub, cub->ray.angle);
		if (v_inter <= h_inter)
			cub->ray.distance = v_inter;
		else
			cub->ray.distance = h_inter;
		render_wall(cub, ray);
		ray++;
		cub->ray.angle += (FOV / 1024);
	}
}

// ------------------  Shooting rays  ------------------ //

int	verify_path(char *map_path)
{
	if (strlen(map_path) <= 4)
		return (0);
	if (strncmp(strrchr(map_path, '.'), ".cub", 5) == 0)
		return (1);
	return (0);
}

void	get_width_heigth(t_cub *cub)
{
	cub->map_width = ft_strlen(cub->map[0]);
	while (cub->map[cub->map_height] != 0)
		cub->map_height++;
}

void find_player_position(t_cub *cub)
{
	int i;
	int j;

	j = 0;
	while (j < cub->map_height)
	{
		i = 0;
		while (i < cub->map_width)
		{
			if (ft_strchr("NSWE", cub->map[j][i]))
			{
				cub->player.p_x = i;
				cub->player.p_y = j;
			}
			i++;
		}
		j++;
	}
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bits_per_pixel - 8;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bits_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	draw_square(t_image *img, int size_x, int size_y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			img_pix_put(img, j + size_x, i + size_y, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_cub *cub)
{
	int playerSize = TILE_SIZE / 2;
	int color = 0x00FF00;

	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE / 2)
	{
		j = 0;
		while (j < TILE_SIZE / 2)
		{
			img_pix_put(&cub->img, j + cub->player.pixel_x - playerSize / 2, i + cub->player.pixel_y - playerSize / 2, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (j < cub->map_width)
		{
			if (cub->map[i][j] == '1')
				draw_square(&cub->img, j * 32, i * 32, 0XFF0000);
			else
				draw_square(&cub->img, j * 32, i * 32, 0X000000);
			j++; 
		}
		i++;
	}
}

void	init_player(t_cub *cub)
{
	cub->player.pixel_x = cub->player.p_x * TILE_SIZE + TILE_SIZE / 2;
	cub->player.pixel_y = cub->player.p_y * TILE_SIZE + TILE_SIZE / 2;
	cub->player.angle = PI;
}

void	init_cub3d(t_cub *cub, char **argv)
{
	cub->map_fd = open(argv[1], O_RDWR);
	cub->map = read_map(cub);
	get_width_heigth(cub);
	find_player_position(cub);
	init_player(cub);
}

void	move_player(t_cub *cub, double move_x, double move_y)
{
	int map_x;
	int map_y;
	int new_x, new_y;

	new_x = roundf(cub->player.pixel_x + move_x);
	new_y = roundf(cub->player.pixel_y + move_y);
	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;

	if (cub->map[map_y][map_x] != '1' && \
 		(cub->map[map_y][cub->player.pixel_x / TILE_SIZE] != '1' && \
			cub->map[cub->player.pixel_y / TILE_SIZE][map_x] != '1'))
	{
		cub->player.pixel_x = new_x;
		cub->player.pixel_y = new_y;
	}
}

void	hook(t_cub *cub, double *move_x, double *move_y)
{
    if (cub->player.r_l == 1)
    {
        *move_x = cos(cub->player.angle) * PLAYER_SPEED;
        *move_y = sin(cub->player.angle) * PLAYER_SPEED;
    }
    if (cub->player.r_l == -1)
    {
        *move_x = -cos(cub->player.angle) * PLAYER_SPEED;
        *move_y = -sin(cub->player.angle) * PLAYER_SPEED;
    }
    if (cub->player.u_d == 1)
    {
        *move_x = -sin(cub->player.angle) * PLAYER_SPEED;
        *move_y = cos(cub->player.angle) * PLAYER_SPEED;
    }
    if (cub->player.u_d == -1)
    {
        *move_x = sin(cub->player.angle) * PLAYER_SPEED;
        *move_y = -cos(cub->player.angle) * PLAYER_SPEED;
    }
    move_player(cub, *move_x, *move_y);
}

static int	game_loop(t_cub *cub)
{
	//draw_map(cub);
	double move_x = 0, move_y = 0;
	hook(cub, &move_x, &move_y);
	draw_player(cub);
	shoot_rays(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (0);
}

static int 	release(int keysym, t_cub *cub)
{
	if (keysym == W || keysym == S)
		cub->player.u_d = 0;
	if (keysym == D || keysym == A)
		cub->player.r_l = 0;
	return (0);
}

static int	handle_input(int keysym, t_cub *cub)
{
	if (keysym == ESCAPE)
		close_window(cub);
	if (keysym == W)
		cub->player.u_d = 1;
	if (keysym == S)
		cub->player.u_d = -1;
	if (keysym == A)
		cub->player.r_l = 1;
	if (keysym == D)
		cub->player.r_l = -1;
	return (0);
}

void	run_cub3d(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, 1024, 512, "CUB3D");
	cub->img.img = mlx_new_image(cub->mlx, 1024, 512);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
										&cub->img.line_length, &cub->img.endian);
	mlx_loop_hook(cub->mlx, &game_loop, cub);
	mlx_hook(cub->win, 2, 1L << 0, &handle_input, cub);
	mlx_hook(cub->win, 3, 1L<<1, &release, cub);
	mlx_loop(cub->mlx);
}


int	main(int argc, char **argv)
{
	static t_cub cub;

 	if (!argv[1] || argc > 2 || !verify_path(argv[1]))
 		return (0);
	init_cub3d(&cub, argv);
	run_cub3d(&cub);
	return (0);
}
