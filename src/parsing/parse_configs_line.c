/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:25:48 by helferna          #+#    #+#             */
/*   Updated: 2024/09/06 16:25:50 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_texture(char *key);
bool	is_color(char *key);
bool	select_color(char key, char *value, t_map *map);
bool	select_texture(char *key, char *value, t_win *win, t_map *map);

/*
	@brief Parses the line and assigns the value to the key in the map structure
	@param line The line to parse
	@param win The window structure
	@param map The map structure
	@return true if the line was parsed successfully, false otherwise
*/
void	remove_trailing_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

bool	handle_color(char *key, char *value, t_map *map, char **key_value)
{
	if (!select_color(key[0], value, map))
	{
		ft_free_array(key_value);
		return (false);
	}
	ft_free_array(key_value);
	return (true);
}

bool	handle_unexpected_line(char *line, char **key_value)
{
	printf("Error: Found unexpected line: %s\n", line);
	ft_free_array(key_value);
	return (false);
}

bool	free_arr_and_return(char **val, bool ret)
{
	ft_free_array(val);
	return (ret);
}

bool	parse_line(char *line, t_win *win, t_map *map)
{
	char	**key_value;
	char	*key;
	char	*value;

	remove_trailing_newline(line);
	key_value = ft_split(line, ' ', 0);
	if (!key_value || ft_array_len(key_value) != 2)
	{
		ft_free_array(key_value);
		return (false);
	}
	key = *key_value;
	value = *(key_value + 1);
	if (is_texture(key))
	{
		if (!select_texture(key, value, win, map))
			return (free_arr_and_return(key_value, false));
		return (free_arr_and_return(key_value, true));
	}
	else if (is_color(key))
		return (handle_color(key, value, map, key_value));
	else
		return (handle_unexpected_line(line, key_value));
}
