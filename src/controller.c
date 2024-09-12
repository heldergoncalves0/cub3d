/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:38:54 by helferna          #+#    #+#             */
/*   Updated: 2024/09/12 11:32:16 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_press(int key, t_cub *cub)
{
	if (key == UP || key == W)
		cub->ctrl->mv_fw = true;
	if (key == DOWN || key == S)
		cub->ctrl->mv_bw = true;
	if (key == A)
		cub->ctrl->mv_lf = true;
	if (key == D)
		cub->ctrl->mv_rt = true;
	if (key == Q || key == LEFT)
		cub->ctrl->rt_lf = true;
	if (key == E || key == RIGHT)
		cub->ctrl->rt_rt = true;
	if (key == KEYMENUS && cub->ctrl->speed > 1)
		cub->ctrl->speed -= 1;
	if (key == KEYMOR && cub->ctrl->speed < 10)
		cub->ctrl->speed += 1;
	if (key == SPACE)
		cub->ctrl->menu *= -1;
	if (key == ESC)
		exit_all(cub);
	return (0);
}

static int	key_release(int key, t_cub *cub)
{
	if (key == UP || key == W)
		cub->ctrl->mv_fw = false;
	if (key == DOWN || key == S)
		cub->ctrl->mv_bw = false;
	if (key == A)
		cub->ctrl->mv_lf = false;
	if (key == G)
		cub->ctrl->mini_map = true;
	if (key == F)
		cub->ctrl->mini_map = false;
	if (key == D)
		cub->ctrl->mv_rt = false;
	if (key == Q || key == LEFT)
		cub->ctrl->rt_lf = false;
	if (key == E || key == RIGHT)
		cub->ctrl->rt_rt = false;
	return (0);
}

t_controller	*init_controller(t_cub *cub)
{
	t_controller	*ctrl;

	ctrl = (t_controller *)malloc(sizeof(t_controller));
	if (!ctrl)
	{
		printf("Error: Failed to allocate controller.\n");
		return (NULL);
	}
	*ctrl = (t_controller){.mv_fw = false, .mv_bw = false, .mv_lf = false, \
					.mv_rt = false, .rt_lf = false, .rt_rt = false, \
				.game_over = false, .mini_map = false, .speed = 1, .menu = 1};
	mlx_hook(cub->win.win, 2, (1L << 0), &key_press, cub);
	mlx_hook(cub->win.win, 3, (1L << 1), &key_release, cub);
	mlx_hook(cub->win.win, 17, 0L, &exit_all, cub);
	return (ctrl);
}
