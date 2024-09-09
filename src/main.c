/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:11 by helferna          #+#    #+#             */
/*   Updated: 2024/09/09 12:52:48 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	run_cub3d(t_cub *cub)
{
	player_move(&cub->player, cub->ctrl, cub->map->map);
	
	win_fill(&cub->win, cub->map->ceiling, cub->map->floor);
	update_camera_plane(&cub->player);

	render_dimension_3d(cub);
	render_2d_map(cub, cub->map, &cub->win, cub->player);

	mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->win.img->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	static t_cub cub;

	if (argc != 2)
	{
		ft_putstr("Error\nInvalid number of arguments\n");
		return (2);
	}
	if (!initialization(&cub) || !parse_cub(&cub, argv[1], &cub.win, cub.map))
	{
		//exit_all(&cub);
		return (2);
	}

	cub.ctrl = init_controller(&cub);
	if (!cub.ctrl)
	{
		exit_all(&cub);
		return (2);
	}
	init_player(&cub.player, cub.map);
	//starting_time here
	mlx_loop_hook(cub.win.mlx, &run_cub3d, &cub);
	mlx_loop(cub.win.mlx);
	return (0);
}
