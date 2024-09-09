/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_colors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:25:40 by helferna          #+#    #+#             */
/*   Updated: 2024/09/06 16:25:42 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
	@brief Checks if the string is a valid color
	@param color The string to check
	@return true if the string is a valid color (between 0 and 255),
		false otherwise
*/
static bool	is_valid_color(char *color)
{
	int	rgb;

	rgb = ft_atoi(color);
	if (rgb < 0 || rgb > 255)
		return (false);
	return (true);
}

/*
	@brief Checks if the string is a digit
	@param str The string to check
	@return true if the string is a digit, false otherwise
*/
static bool	ft_isdigit_str(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/*
	@brief Assigns the value to the color structure
	@param value The string that value to assign to the color
	@param The string should be in the format "r,g,b"  where r, g,
		b are integers between 0 and 255
	color The color structure to assign the value to
	@return true if the value was assigned successfully, false otherwise
*/
static bool	assign_color(char *value, int *color)
{
	char	**rgb;

	rgb = ft_split(value, ',', 0);
	if (!rgb)
		return (false);
	if (ft_array_len(rgb) != 3)
	{
		printf("Error: Color must be in the format {RRR,GGG,BBB}\n");
		ft_free_array(rgb);
		return (false);
	}
	if (!ft_isdigit_str(*rgb) || !is_valid_color(*rgb) || \
		!ft_isdigit_str(*(rgb + 1)) || !is_valid_color(*(rgb + 1)) || \
		!ft_isdigit_str(*(rgb + 2)) || !is_valid_color(*(rgb + 2)))
	{
		printf("Error: Invalid color, values should be between 0 and 255\n");
		ft_free_array(rgb);
		return (false);
	}
	*color = rgb_to_hex(ft_atoi(*rgb), ft_atoi(*(rgb + 1)), \
		ft_atoi(*(rgb + 2)));
	ft_free_array(rgb);
	return (true);
}

static bool	check_and_assign_color(char *value, int *color_field)
{
	if (*color_field != -1)
	{
		printf("Error: Color specified more than once.\n");
		return (false);
	}
	else if (!assign_color(value, color_field))
	{
		printf("Error: Invalid color key\n");
		return (false);
	}
	return (true);
}

/*
	@brief Parses the color configuration
	@param key The key of the configuration
	@param value The value of the configuration
	@param map The map structure to assign the color to
	@return true if the color was assigned successfully, false otherwise
*/
bool	select_color(char key, char *value, t_map *map)
{
	if (key == 'F')
		return (check_and_assign_color(value, &map->floor));
	else if (key == 'C')
		return (check_and_assign_color(value, &map->ceiling));
	else
	{
		printf("Error: Invalid color key\n");
		return (false);
	}
}
