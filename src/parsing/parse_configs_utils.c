/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:25:30 by helferna          #+#    #+#             */
/*   Updated: 2024/09/06 16:25:32 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_space(char c);

/*
	@brief Checks if the key is a texture
	@param key The key to check
	@return true if the key is a texture, false otherwise
*/
bool	is_texture(char *key)
{
	return (!ft_strncmp(key, "NO", 3) || !ft_strncmp(key, "SO", 3) \
		|| !ft_strncmp(key, "WE", 3) || !ft_strncmp(key, "EA", 3));
}

/*
	@brief Checks if the key is a color
	@param key The key to check
	@return true if the key is a color, false otherwise
*/
bool	is_color(char *key)
{
	return (!ft_strncmp(key, "F", 2) || !ft_strncmp(key, "C", 2));
}

/*
	@brief Checks if the line is empty
	@param line The line to check
	@return true if the line is empty, false otherwise
*/
bool	is_line_empty(char *line)
{
	while (line && *line)
	{
		if (!is_space((unsigned char)*line))
			return (false);
		line++;
	}
	return (true);
}

/*
	@brief Checks if all the configurations are set
	@param map The map structure
	@return true if all the configurations are set, false otherwise
*/
bool	all_configs_set(t_map *map)
{
	if (map->floor == -1 || map->ceiling == -1 || \
		!map->no || !map->so || \
		!map->ea || !map->we)
		return (false);
	return (true);
}

/*
	@brief Gets the next line from the file descriptor
	@param fd The file descriptor to read the line from
	@return The line read from the file descriptor
*/
bool	gnl(int fd, char **line)
{
	*line = get_next_line(fd);
	if (!*line)
		return (false);
	return (true);
}
