/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bye.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:42:11 by helferna          #+#    #+#             */
/*   Updated: 2024/09/09 12:17:34 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

size_t	ft_array_len(char **array)
{
	size_t	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	destroy_image(void *mlx, t_image *img)
{
	if (!mlx || !img || !img->img)
		return ;
	mlx_destroy_image(mlx, img->img);
	if (img)
		free(img);
}

void	destroy_map(void *mlx, t_map *map)
{
	if (!mlx || !map)
		return ;
	destroy_image(mlx, map->no);
	destroy_image(mlx, map->so);
	destroy_image(mlx, map->we);
	destroy_image(mlx, map->ea);
	if (map->map)
		ft_free_array(map->map);
	if (map)
		free(map);
}

void	destroy_window(t_win *win)
{
	destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->win);
	// mlx_destroy_display(win->mlx);
	// if (win->mlx)
	// 	free(win->mlx);
	// if (win)
	// 	free(win);
}

void	free_cub(t_cub *cub)
{
	if (cub->map)
		destroy_map(cub->win.mlx, cub->map);
	destroy_window(&cub->win);
	// if (cub->ctrl)
	// 	free(cub->ctrl);
	// if (cub)
	// 	free(cub);
}

int	exit_all(t_cub *cub)
{
	printf("You exited Cub3D\n");
	free_cub(cub);
	exit(0);
}