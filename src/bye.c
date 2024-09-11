/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bye.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:42:11 by helferna          #+#    #+#             */
/*   Updated: 2024/09/11 18:02:16 by helferna         ###   ########.fr       */
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

void	free_cub(t_cub *cub)
{
	if (cub->map)
	{
		destroy_image(cub->win.mlx, cub->map->no);
		destroy_image(cub->win.mlx, cub->map->so);
		destroy_image(cub->win.mlx, cub->map->we);
		destroy_image(cub->win.mlx, cub->map->ea);
		if (cub->map->map)
			ft_free_array(cub->map->map);
		free(cub->map);
	}
	destroy_image(cub->win.mlx, cub->win.img);
	if (cub->win.win)
	{
		mlx_destroy_window(cub->win.mlx, cub->win.win);
		mlx_destroy_display(cub->win.mlx);
		free(cub->win.mlx);
	}
	if (cub->ctrl)
		free(cub->ctrl);
	if (!cub->win.win && cub->win.mlx)
	{
		mlx_destroy_display(cub->win.mlx);
		free(cub->win.mlx);
	}
}

int	exit_all(t_cub *cub)
{
	printf("You exited Cub3D\n");
	free_cub(cub);
	exit(0);
}
