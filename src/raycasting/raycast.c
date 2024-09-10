/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:36:09 by helferna          #+#    #+#             */
/*   Updated: 2024/09/10 17:39:03 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// loggers
//void		__log_results(t_computes *computes);
//void		__log_computes(t_computes *computes);
// more computation functions
void		__render_computes(t_computes *computes, t_player *player);

static void	__dda(t_computes *computes, char **map)
{
	computes->hit = false;
	while (true)
	{
		if (computes->step_size.x < computes->step_size.y)
		{
			computes->step_size.x += computes->delta.x;
			computes->map.x += computes->step.x;
			computes->side = 0;
		}
		else
		{
			computes->step_size.y += computes->delta.y;
			computes->map.y += computes->step.y;
			computes->side = 1;
		}
		if (computes->map.x < 0 || computes->map.y < 0)
			break ;
		if (map[computes->map.y]
			&& map[computes->map.y][computes->map.x] == '1')
		{
			computes->hit = true;
			break ;
		}
	}
}

static void	__sides(t_computes *computes, t_player *player)
{
	if (computes->ray.x < 0)
	{
		computes->step.x = -1;
		computes->step_size.x = (player->pos.x - computes->map.x)
			* computes->delta.x;
	}
	else
	{
		computes->step.x = 1;
		computes->step_size.x = ((computes->map.x + 1.0) - player->pos.x)
			* computes->delta.x;
	}
	if (computes->ray.y < 0)
	{
		computes->step.y = -1;
		computes->step_size.y = (player->pos.y - computes->map.y)
			* computes->delta.y;
	}
	else
	{
		computes->step.y = 1;
		computes->step_size.y = ((computes->map.y + 1.0) - player->pos.y)
			* computes->delta.y;
	}
}

static void	__deltas(t_computes *computes)
{
	computes->delta.x = fabs(1 / computes->ray.x);
	computes->delta.y = fabs(1 / computes->ray.y);
}

static void	__helper_vecs(t_computes *computes, t_player *player, double camera)
{
	computes->map.x = (int)player->pos.x;
	computes->map.y = (int)player->pos.y;
	computes->ray.x = player->dir.x + (player->plane.x * camera);
	computes->ray.y = player->dir.y + (player->plane.y * camera);
}

void	raycast(int column, t_map *map, t_player *player, t_computes *computes)
{
	double	camera;

	camera = ((2 * column / (double)WINWIDTH) - 1);
	__helper_vecs(computes, player, camera);
	__deltas(computes);
	__sides(computes, player);
	__dda(computes, map->map);
	__render_computes(computes, player);
	return ;
}
