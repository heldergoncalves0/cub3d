/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:30:13 by helferna          #+#    #+#             */
/*   Updated: 2024/06/04 02:11:42 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	inter_check(float angle, float *inter, float *step, int is_horizon)
// {
// 	if (is_horizon)
// 	{
// 		if (angle > 0 && angle < PI)
// 		{
// 			*inter += TILE_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	else
// 	{
// 		if (!(angle > PI / 2 && angle < 3 * PI / 2)) 
// 		{
// 			*inter += TILE_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	return (1);
// }

// int	unit_circle(float angle, char axis)
// {
// 	if (axis == 'x')
// 	{
// 		if (angle > 0 && angle < PI)
// 			return (1);
// 	}
// 	else
// 	{
// 		if (angle > PI / 2 && angle < 3 * PI / 2)
// 			return (1);
// 	}
// 	return (0);
// }

// float	get_h_inter(t_cub *cub, float angle)
// {
// 	float	y_step;
// 	float	x_step;
// 	float	h_y;
// 	int		pixel;
// 	float	h_x;

// 	y_step = TILE_SIZE;
// 	x_step = TILE_SIZE / tan(angle);
// 	h_y = (floor(cub->player.p_y / TILE_SIZE) * TILE_SIZE);
// 	h_x = cub->player.p_x + ((h_y - cub->player.p_x) / tan(angle));
// 	pixel = inter_check(angle, &h_y, &y_step, 1);
// 	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0))
// 		x_step *= -1;
// 	//CHECK WALL HIT
// 	return (sqrt(pow(h_x - cub->player.p_x, 2) + pow(h_y - cub->player.p_y, 2)));
// }

// float	get_v_inter(t_cub *cub, float angle)
// {
// 	float	x_step;
// 	float	y_step;
// 	float	v_x;
// 	int 	pixel;
// 	float	v_y;

// 	x_step = TILE_SIZE / tan(angle);
// 	y_step = TILE_SIZE;
// 	v_x = (floor(cub->player.p_x / TILE_SIZE) * TILE_SIZE);
// 	v_y = cub->player.p_y + ((v_x - cub->player.p_y) / tan(angle));
// 	pixel = inter_check(angle, &v_x, &x_step, 0);
// 	// if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0))
// 	// 	y_step *= -1;
// 	//CHECK WALL HIT
// 	return (sqrt(pow(v_x - cub->player.p_x, 2) + pow(v_y - cub->player.p_y, 2)));
// }

// void	shoot_rays(t_cub *cub)
// {
// 	int		ray;
// 	float	h_inter;
// 	float	v_inter;

// 	h_inter = 0;
// 	v_inter = 0;
// 	ray = 0;
// 	cub->ray.angle = cub->player.angle - FOV / 2;
// 	while (ray < 1024)
// 	{
// 		h_inter = get_h_inter(cub, cub->ray.angle);
// 		v_inter = get_v_inter(cub, cub->ray.angle);
// 		if (v_inter <= h_inter)
// 			cub->ray.distance = v_inter;
// 		else
// 			cub->ray.distance = h_inter;
// 		render_wall(cub, ray);
// 		ray++;
// 		cub->ray.angle += (FOV / 1024);
// 	}
// }
