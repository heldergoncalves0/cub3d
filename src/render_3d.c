/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:38:51 by helferna          #+#    #+#             */
/*   Updated: 2024/09/10 19:55:45 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Calculate the texture to use for the wall based on the direction
t_image	*get_texture(t_computes *computes, t_map *map)
{
	if (computes->dir == 'N')
		return (map->no);
	else if (computes->dir == 'S')
		return (map->so);
	else if (computes->dir == 'W')
		return (map->we);
	else if (computes->dir == 'E')
		return (map->ea);
	return (NULL);
}

// Calculate the texture position and delta for a pixel on the wall
static double	get_delta_pos(t_image *texture, t_vector *pos,
		int wall_height)
{
	double	delta;

	delta = (double)texture->height / wall_height;
	if (wall_height < WINHEIGHT)
	{
		pos->y = 0.0;
		return (delta);
	}
	pos->y = (((double)(wall_height - WINHEIGHT) / 2) / wall_height)
		* texture->height;
	delta = 1 - ((double)(wall_height - WINHEIGHT) / wall_height);
	delta = (delta * texture->height) / WINHEIGHT;
	return (delta);
}

// Set the pixel color of the wall texture to the image
void	set_wall_texture(t_image *image, t_coords image_cords, \
		t_image *texture, t_vector texture_pos)
{
	char	*src;
	char	*dest;

	src = texture->addr + ((int)(texture_pos.y) *(texture->line_length) \
						+ (int)(texture_pos.x) *(texture->bits_per_pixel / 8));
	dest = image->addr +((int)(image_cords.y) *(image->line_length) \
		+ (int)(image_cords.x) *(image->bits_per_pixel / 8));
	*(unsigned int *)dest = *(unsigned int *)src;
}

/*
given the map and the player and the computes
draw the wall for each pixel column with texture
*/
void	create_wall(t_image *image, t_computes *computes, t_map *map)
{
	double			delta;
	t_coords		cords;
	t_image			*texture;
	t_computes		*computed;
	t_vector		texture_pos;

	cords = (t_coords){-1, -1};
	while (++cords.x < WINWIDTH)
	{
		computed = &computes[cords.x];
		texture = get_texture(computed, map);
		if (computed->dir == 'S' || computed->dir == 'W')
			texture_pos.x = ((double)texture->width * (1 - computed->wall_x));
		else
			texture_pos.x = (double)texture->width * computed->wall_x;
		delta = get_delta_pos(texture, &texture_pos, computed->wall_height);
		cords.y = computed->start_wall - 1;
		while (++cords.y < computed->end_wall)
		{
			set_wall_texture(image, cords, texture, texture_pos);
			texture_pos.y += delta;
			if (texture_pos.y >= texture->height - 1)
				break ;
		}
	}
}

void	render_dimension_3d(t_cub *cub)
{
	unsigned int	i;

	i = -1;
	while (++i < WINWIDTH)
		raycast(i, cub->map, &cub->player, &cub->cols[i]);
	create_wall(cub->win.img, cub->cols, cub->map);
}
