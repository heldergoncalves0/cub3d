/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:24:57 by helferna          #+#    #+#             */
/*   Updated: 2024/09/11 15:14:23 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
	@brief Checks if the key is a texture
	@param key The key to check
	@return true if the key is a texture, false otherwise
*/
bool	check_borders(char **map, int i, int j)
{
	if (j == 0 || i == 0 || !map[i + 1] || !map[i][j + 1] || !map[i][j - 1] ||
			!map[i - 1][j] || map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
				map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		return (false);
	return (true);
}

/*
	@brief Checks if the character is a valid player character
	@param c The character to check
	@return true if the character is a valid player character, false otherwise
*/
bool	is_valid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*
	@brief Checks if the character is a valid map character
	@param c The character to check
	@return true if the character is a valid map character, false otherwise

*/
bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\n');
}

/*
	@brief Checks if the character is a space
	@param c The character to check
	@return true if the character is a space, false otherwise
*/
bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
