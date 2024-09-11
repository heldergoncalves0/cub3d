/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:55:02 by rprocopi          #+#    #+#             */
/*   Updated: 2024/09/11 18:29:25 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_str(t_win data, int x, int y, char *str)
{
	mlx_string_put(data.mlx, data.win, x, y, 0xffffff, str);
}

void	print_menu(t_win data)
{
	int		y;

	y = 0;
	mlx_string_put(data.mlx, data.win, 20, y += 430, 0xffa500, \
		"//// CONTROLS ////");
	print_str(data, 10, y += 20, "Press 'ESC' to close");
	print_str(data, 10, y += 20, "Press 'G' to show MiniMap");
	print_str(data, 10, y += 20, "Press 'F' to hide MiniMap");
	print_str(data, 10, y += 20, "Speed: press '-' or '+'");
	print_str(data, 10, y += 20, "Move : press arrow keys or 'WS'");
	print_str(data, 10, y += 20, "Rotation: press '<-' '->' or 'QE'");
	print_str(data, 10, y += 20, "Shift to the side: press 'A' or 'D'");
	print_str(data, 10, y += 20, "Press SPACE to hide or show menu");
}
