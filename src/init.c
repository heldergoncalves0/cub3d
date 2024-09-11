/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:54:56 by helferna          #+#    #+#             */
/*   Updated: 2024/09/11 18:20:28 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	init_mlx(t_cub *cub)
{
	cub->win.mlx = mlx_init();
	if (!cub->win.mlx)
	{
		printf("Error: Failed to initialize mlx.\n");
		return (false);
	}
	return (true);
}

bool	init_win(t_cub *cub)
{
	cub->win.win = mlx_new_window(cub->win.mlx, WINWIDTH, WINHEIGHT,
			"cub3D");
	if (!cub->win.win)
	{
		printf("Error: Failed to create window.\n");
		return (false);
	}
	return (true);
}

bool	init_map(t_cub *cub)
{
	cub->map = (t_map *)malloc(sizeof(t_map));
	if (!cub->map)
	{
		printf("Error: Failed to allocate memory for map.\n");
		return (false);
	}
	*cub->map = (t_map){.map = NULL, .floor = -1, .ceiling = -1, .no = NULL,
		.so = NULL, .we = NULL, .ea = NULL};
	return (true);
}

bool	init_image(t_cub *cub)
{
	cub->win.img->img = mlx_new_image(cub->win.mlx, WINWIDTH, WINHEIGHT);
	if (!cub->win.img->img)
	{
		printf("Error: Failed to create image.\n");
		return (false);
	}
	cub->win.img->addr = mlx_get_data_addr(cub->win.img->img,
			&cub->win.img->bits_per_pixel, &cub->win.img->line_length,
			&cub->win.img->endian);
	if (!cub->win.img->addr)
	{
		printf("Error: Failed to get image address.\n");
		mlx_destroy_image(cub->win.mlx, cub->win.img->img);
		return (false);
	}
	return (true);
}

bool	initialization(t_cub *cub)
{
	if (!init_mlx(cub))
		return (false);
	if (!init_map(cub))
		return (false);
	cub->win.img = (t_image *)malloc(sizeof(t_image));
	if (!cub->win.img)
	{
		printf("Error: Failed to allocate memory for image.\n");
		return (false);
	}
	if (!init_image(cub))
		return (false);
	cub->win.img->width = WINWIDTH;
	cub->win.img->height = WINHEIGHT;
	return (true);
}
