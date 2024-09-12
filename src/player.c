/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:51:04 by helferna          #+#    #+#             */
/*   Updated: 2024/09/12 09:21:05 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_vector(t_vector *vec, double angle);

// void	__display_player_info(t_player *player, char dir)
// {
// 	printf("------------------------------\n");
// 	printf("Player: \n");
// 	printf("Found at: (%d, %d)\n", (int)player->pos.x, \
// 		(int)player->pos.y);
// 	printf("Direction: (%c)\n", dir);
// }

bool	__player_exists_here(t_map *map, t_player *player, unsigned int x,
		unsigned int y)
{
	if (map->map[y][x] == 'N')
		player->dir = (t_vector){.x = 0, .y = -1};
	else if (map->map[y][x] == 'S')
		player->dir = (t_vector){.x = 0, .y = 1};
	else if (map->map[y][x] == 'E')
		player->dir = (t_vector){.x = 1, .y = 0};
	else if (map->map[y][x] == 'W')
		player->dir = (t_vector){.x = -1, .y = 0};
	else
		return (false);
	player->pos = (t_vector){.x = (double)x + 0.5, .y = (double)y + 0.5};
	map->map[y][x] = '0';
	return (true);
}

void	_player_start_pos(t_map *map, t_player *player)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (map->map && map->map[y])
	{
		x = 0;
		while (map->map[y] && map->map[y][x])
		{
			if (__player_exists_here(map, player, x, y))
				return ;
			x++;
		}
		y++;
	}
	return ;
}

void	update_camera_plane(t_player *player)
{
	t_vector	plane;

	plane = (t_vector){.x = player->dir.x, .y = player->dir.y};
	rotate_vector(&plane, 90);
	player->plane.x = plane.x;
	player->plane.y = plane.y;
}

void	init_player(t_player *player, t_map *map)
{
	_player_start_pos(map, player);
	update_camera_plane(player);
}
