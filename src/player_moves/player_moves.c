/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:29:45 by helferna          #+#    #+#             */
/*   Updated: 2024/03/12 16:59:39 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void move_player(t_cub *cub, double move_x, double move_y)
// {
// 	int  map_grid_y;
// 	int  map_grid_x;
// 	int  new_x;
// 	int  new_y;

// 	printf("move_x: %f, move_y: %f", move_x, move_y);
// 	new_x = roundf(cub->player.p_x + move_x); // get the new x position
// 	new_y = roundf(cub->player.p_y + move_y); // get the new y position
// 	map_grid_x = (new_x / 32); // get the x position in the map
// 	map_grid_y = (new_y / 32); // get the y position in the map
// 	if (cub->map[map_grid_y][map_grid_x] != '1' && \
// 		(cub->map[map_grid_y][cub->player.p_x / 32] != '1' && \
// 			cub->map[cub->player.p_y / 32][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
// 	{
// 		cub->player.pp_x = new_x;
// 		cub->player.pp_y = new_y;
// 	}
// }

// void	move_player_up(t_cub *cub)
// {
// 	double move_x;
// 	double move_y;

// 	move_x = cos(M_PI / 2) * 4;
// 	move_y = sin(M_PI / 2) * 4;
// 	move_player(cub, move_x, move_y);
// }