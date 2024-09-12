/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:55:02 by rprocopi          #+#    #+#             */
/*   Updated: 2024/09/12 11:26:12 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_str(t_win data, int x, int y, char *str)
{
	mlx_string_put(data.mlx, data.win, x, y, 0xffffff, str);
}

void	printf_nbr(t_win data, int x, int y, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	mlx_string_put(data.mlx, data.win, x, y, 0xffffff, str);
	free (str);
}

void	print_menu(t_cub *data)
{
	int		y;

	y = 0;
	mlx_string_put(data->win.mlx, data->win.win, 20, y += 400, 0xffa500, \
		"//// CONTROLS ////");
	print_str(data->win, 10, y += 20, "Press 'ESC' to close");
	print_str(data->win, 10, y += 20, "Press 'G' to show MiniMap");
	print_str(data->win, 10, y += 20, "Press 'F' to hide MiniMap");
	print_str(data->win, 10, y += 20, "Speed: press '-' or '+'");
	print_str(data->win, 10, y += 20, "Move : press arrow keys or 'WS'");
	print_str(data->win, 10, y += 20, "Rotation: press '<-' '->' or 'QE'");
	print_str(data->win, 10, y += 20, "Shift to the side: press 'A' or 'D'");
	print_str(data->win, 10, y += 20, "Press SPACE to hide or show menu");
	print_str(data->win, 10, y += 20, "Speed: ");
	printf_nbr(data->win, 50, y += 0, data->ctrl->speed);
}
