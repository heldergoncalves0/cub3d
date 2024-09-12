/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:11 by helferna          #+#    #+#             */
/*   Updated: 2024/09/12 09:59:33 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	run_cub3d(t_cub *cub)
{
	player_move(&cub->player, cub->ctrl, cub->map->map);
	win_fill(&cub->win, cub->map->ceiling, cub->map->floor);
	update_camera_plane(&cub->player);
	render_dimension_3d(cub);
	if (cub->ctrl->mini_map)
		render_2d_map(cub, cub->map, &cub->win, cub->player);
	mlx_put_image_to_window(cub->win.mlx, cub->win.win, \
		cub->win.img->img, 0, 0);
	if (cub->ctrl->menu == 1)
		print_menu(cub);
	return (0);
}

int	main(int argc, char **argv)
{
	static t_cub	cub;

	if (argc != 2)
		return (printf("Error\nInvalid number of arguments\n"), 2);
	if (!initialization(&cub) || !parse_cub(&cub, argv[1], &cub.win, cub.map))
		return (2);
	if (!init_win(&cub))
		return (2);
	cub.ctrl = init_controller(&cub);
	if (!cub.ctrl)
		return (exit_all(&cub), 2);
	init_player(&cub.player, cub.map);
	mlx_loop_hook(cub.win.mlx, &run_cub3d, &cub);
	mlx_loop(cub.win.mlx);
	return (0);
}
