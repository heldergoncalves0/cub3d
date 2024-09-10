/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:36:00 by helferna          #+#    #+#             */
/*   Updated: 2024/09/10 17:39:18 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* calculate the distance to the wall based on the side hit */
static void	__wall_info(t_computes *computes, t_player *player)
{
	if (computes->side == 0)
		computes->dist_to_wall = (computes->map.x - player->pos.x + (1
					- computes->step.x) / 2) / computes->ray.x;
	else
		computes->dist_to_wall = (computes->map.y - player->pos.y + (1
					- computes->step.y) / 2) / computes->ray.y;
}

/* calculate which side the hit is -> "NEWS" */
static void	__hit_infos(t_computes *computes)
{
	if (computes->side == 0)
	{
		if (computes->ray.x > 0)
			computes->dir = 'E';
		else
			computes->dir = 'W';
	}
	else
	{
		if (computes->ray.y > 0)
			computes->dir = 'S';
		else
			computes->dir = 'N';
	}
}

/* these computed variables are used in the 3D rendering */
void	__render_computes(t_computes *computes, t_player *player)
{
	__wall_info(computes, player);
	__hit_infos(computes);
	computes->wall_height = (int)((double)WINHEIGHT / computes->dist_to_wall)
		*0.6;
	computes->start_wall = fmax(0, (WINHEIGHT / 2) - (computes->wall_height
				/ 2));
	computes->end_wall = fmin(WINHEIGHT, (WINHEIGHT / 2)
			+ (int)ceil(computes->wall_height / 2));
	computes->hit_pos.x = player->pos.x + computes->dist_to_wall
		* computes->ray.x;
	computes->hit_pos.y = player->pos.y + computes->dist_to_wall
		* computes->ray.y;
	if (computes->dir == 'S' || computes->dir == 'N')
		computes->wall_x = computes->hit_pos.x - floor(computes->hit_pos.x);
	else
		computes->wall_x = computes->hit_pos.y - floor(computes->hit_pos.y);
}
