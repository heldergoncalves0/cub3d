/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:25:56 by helferna          #+#    #+#             */
/*   Updated: 2024/09/11 16:32:05 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	can_read_file(char *path, char *format);

/*
	@brief Assigns the value to the texture structure
	@param value The string that value to assign to the texture
	@param texture The texture structure to assign the value to
	@return true if the value was assigned successfully, false otherwise
*/
t_image	*assign_texture(void *mlx, char *path)
{
	t_image	*img;

	if (!can_read_file(path, ".xpm"))
	{
		printf("Error: Failed to read file:'%s'\n", path);
		return (NULL);
	}
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
	{
		printf("Error: Failed to allocate memory for texture.\n");
		return (NULL);
	}
	img->img = mlx_xpm_file_to_image(mlx, path, &(img->width), &(img->height));
	if (img->width > 128 || img->height > 128)
	{
		printf("Error: '%s' image size should be %d", path, 128);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
		&(img->line_length),
			&(img->endian));
	return (img);
}

bool	try_assign_color(void *mlx, char *value, t_image **img)
{
	*img = assign_texture(mlx, value);
	if (!*img)
		return (false);
	return (true);
}

bool	select_texture(char *key, char *value, t_win *win, t_map *map)
{
	if (!map || !win)
	{
		printf("Error: Invalid map or window structure\n");
		return (false);
	}
	if (!can_read_file(value, ".xpm"))
	{
		printf("Error: Failed to read texture file: %s\n", \
			value);
		return (false);
	}
	if (!ft_strncmp(key, "NO", 3) && !map->no)
		return (try_assign_color(win->mlx, value, &map->no));
	else if (!ft_strncmp(key, "SO", 3) && !map->so)
		return (try_assign_color(win->mlx, value, &map->so));
	else if (!ft_strncmp(key, "WE", 3) && !map->we)
		return (try_assign_color(win->mlx, value, &map->we));
	else if (!ft_strncmp(key, "EA", 3) && !map->ea)
		return (try_assign_color(win->mlx, value, &map->ea));
	else
	{
		printf("Error: Failed to assign texture\n");
		return (false);
	}
	return (true);
}
