/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:12:33 by helferna          #+#    #+#             */
/*   Updated: 2024/09/05 21:31:51 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_line_empty(char *line);
bool	all_configs_set(t_map *map);
bool	gnl(int fd, char **line);
bool	parse_line(char *line, t_win *win, t_map *map);

bool	parse_configs(int map_fd, t_win *win, t_map *map)
{
	char	*line;

	while (!all_configs_set(map) && gnl(map_fd, &line) == true)
	{
		if (!line)
			break ;
		if (is_line_empty(line))
		{
			free(line);
			continue ;
		}
		if (!parse_line(line, win, map))
		{
			printf("Error: Failed to parse line: %s\n", \
					line);
			printf("Error: Missing configurations\n");
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}
