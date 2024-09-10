/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:54:56 by helferna          #+#    #+#             */
/*   Updated: 2024/09/10 13:55:22 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// bool	init_win(t_cub *cub)
// {
// 	cub->win = (t_win *)malloc(sizeof(t_win));
// 	if (!&cub->win)
// 	{
// 		printf(STDERR_FILENO, 
// 			"Error: Failed to allocate memory for window.\n");
// 		return (false);
// 	}
// 	return (true);
// }

bool	init_mlx(t_cub *cub)
{
	cub->win.mlx = mlx_init();
	if (!cub->win.mlx)
	{
		printf("Error: Failed to initialize mlx.\n");
		//free(&cub->win);
		return (false);
	}
	cub->win.win = mlx_new_window(cub->win.mlx, WinWidth, WinHeight,
			"cub3D");
	if (!cub->win.win)
	{
		printf("Error: Failed to create window.\n");
		// free(&cub->win);
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
		//free(cub->win.win);
		//free(&cub->win);
		return (false);
	}
	*cub->map = (t_map){.map = NULL, .floor = -1, .ceiling = -1, .no = NULL,
		.so = NULL, .we = NULL, .ea = NULL};
	return (true);
}

bool	init_image(t_cub *cub)
{
	cub->win.img->img = mlx_new_image(cub->win.mlx, WinWidth, WinHeight);
	if (!cub->win.img->img)
	{
		printf("Error: Failed to create image.\n");
		// free(cub->win.img);
		// free(&cub->map);
		// free(cub->win.win);
		// free(&cub->win);
		return (false);
	}
	cub->win.img->addr = mlx_get_data_addr(cub->win.img->img,
			&cub->win.img->bits_per_pixel, &cub->win.img->line_length,
			&cub->win.img->endian);
	if (!cub->win.img->addr)
	{
		printf("Error: Failed to get image address.\n");
		mlx_destroy_image(cub->win.mlx, cub->win.img->img);
		// free(cub->win.img);
		// free(cub->map);
		// free(cub->win.win);
		// free(&cub->win);
		return (false);
	}
	return (true);
}

bool	initialization(t_cub *cub)
{
	// if (!init_win(cub))
	// 	return (false);
	if (!init_mlx(cub))
		return (false);
	if (!init_map(cub))
		return (false);
	cub->win.img = (t_image *)malloc(sizeof(t_image));
	if (!cub->win.img)
	{
		printf("Error: Failed to allocate memory for image.\n");
		//free(&cub->map);
		//free(&cub->win.win);
		//free(&cub->win);
		return (false);
	}
	if (!init_image(cub))
		return (false);
	cub->win.img->width = WinWidth;
	cub->win.img->height = WinHeight;
	return (true);
}