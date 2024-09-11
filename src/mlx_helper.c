/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:10:09 by helferna          #+#    #+#             */
/*   Updated: 2024/09/10 19:16:28 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_image *img, t_coords cord, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, cord.x + j, cord.y + i, color);
			j++;
		}
		i++;
	}
}

void	win_fill(t_win *win, int ceiling_color, int floor_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINHEIGHT / 2)
	{
		x = 0;
		while (x < WINWIDTH)
			put_pixel(win->img, x++, y, ceiling_color);
		y++;
	}
	y = WINHEIGHT / 2;
	while (y < WINHEIGHT)
	{
		x = 0;
		while (x < WINWIDTH)
			put_pixel(win->img, x++, y, floor_color);
		y++;
	}
}
