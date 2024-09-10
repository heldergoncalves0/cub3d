/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:12:10 by helferna          #+#    #+#             */
/*   Updated: 2024/09/10 17:39:03 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_line(t_image *img, t_vector *start, t_vector *line_len,
		int color)
{
	t_vector	cur;
	t_vector	iter;
	t_vector	delta;

	iter = (t_vector){-1, sqrt(pow(line_len->x, 2) + pow(line_len->y, 2))};
	cur = (t_vector){start->x, start->y};
	delta = (t_vector){line_len->x / iter.y, line_len->y / iter.y};
	while (++iter.x <= iter.y)
	{
		put_pixel(img, (int)floor(cur.x), (int)floor(cur.y), color);
		cur.x += delta.x;
		cur.y += delta.y;
	}
}

static void	draw_rays(t_cub *cub)
{
	t_vector	player_cord;
	t_vector	hit_cord;
	int			i;

	player_cord.x = cub->player.pos.x * TILE_SIZE;
	player_cord.y = cub->player.pos.y * TILE_SIZE;
	i = -1;
	while (++i < WINWIDTH)
	{
		hit_cord.x = cub->cols[i].hit_pos.x * TILE_SIZE - player_cord.x;
		hit_cord.y = cub->cols[i].hit_pos.y * TILE_SIZE - player_cord.y;
		draw_line(cub->win.img, &player_cord, &hit_cord, 0x00FF3300);
	}
}

void	draw_square_db(t_image *img, double x, double y, int size)
{
	double	i;
	double	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, x + j, y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	render_2d_map(t_cub *cub, t_map *map, t_win *win, t_player player)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] && map->map[y][x] == '1')
				draw_square(win->img, (t_coords){x * TILE_SIZE, y
					* TILE_SIZE}, TILE_SIZE, 0xC8FFFFFF);
			else if (map->map[y][x] && map->map[y][x] == '0')
				draw_square(win->img, (t_coords){x * TILE_SIZE, y
					* TILE_SIZE}, TILE_SIZE, 0x00000000);
			x++;
		}
		y++;
	}
	draw_rays(cub);
	draw_square_db(win->img, player.pos.x * TILE_SIZE, player.pos.y
		* TILE_SIZE, TILE_SIZE / 4);
}
