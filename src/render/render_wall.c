/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:43:46 by helferna          #+#    #+#             */
/*   Updated: 2024/04/08 20:02:04 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

static int	get_color(t_cub *cub, int flag)
{
	cub->ray.angle = nor_angle(cub->ray.angle);
	if (flag == 0)
	{
		if (cub->ray.angle > M_PI / 2 && cub->ray.angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF);
		else
			return (0xB5B5B5FF); 
	}
	else
	{
		if (cub->ray.angle > 0 && cub->ray.angle < M_PI)
			return (0xF5F5F5FF);
		else
			return (0xF5F5F5FF);
	}
}

void draw_wall(t_cub *cub, int ray, int t_pix, int b_pix)
{
	int color;

	color = get_color(cub, 1);
	while (t_pix < b_pix)
		img_pix_put(&cub->img,	ray, t_pix++, color);
}

void	render_wall(t_cub *cub, int ray)
{
	double wall_height;
	double bottom_pixel;
	double top_pixel;

	cub->ray.distance *= cos(nor_angle(cub->ray.angle - cub->player.angle));
	wall_height = (TILE_SIZE * cub->ray.distance) / (1024 / tan(FOV / 2));
	bottom_pixel = ((512 / 2) + (wall_height / 2));
	top_pixel = ((512 / 2) - (wall_height / 2));
	//printf("top_pixel: %f, bottom_pixel: %f\n", top_pixel, bottom_pixel);
	draw_wall(cub, ray, top_pixel, bottom_pixel);
}
