/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:13:23 by helferna          #+#    #+#             */
/*   Updated: 2024/09/11 17:33:01 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	parse_map(int map_fd, t_map **map);
bool	parse_configs(int map_fd, t_win *win, t_map *map);
bool	is_line_empty(char *line);
bool	check_borders(char **map, int i, int j);

bool	check_file_format(char *file, char *format)
{
	char	*str;

	str = ft_strrchr(file, '.');
	if (str && !ft_strncmp(str, format, ft_strlen(file)))
		return (true);
	return (false);
}

bool	can_read_file(char *path, char *format)
{
	int	fd;

	fd = -1;
	if (!check_file_format(path, format))
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

bool	do_stuff(t_cub *cub, int map_fd, char *path)
{
	free_cub(cub);
	printf("Error\n%s", path);
	if (map_fd != -1)
		close(map_fd);
	return (false);
}

bool	parse_cub(t_cub *cub, char *path, t_win *win, t_map *map)
{
	int	map_fd;

	map_fd = -1;
	if (!can_read_file(path, ".cub"))
		return (do_stuff(cub, map_fd, "Failed to read map file\n"));
	map_fd = open(path, O_RDONLY);
	if (map_fd == -1 || !parse_configs(map_fd, win, map))
		return (do_stuff(cub, map_fd, "Failed to parse configs\n"));
	if (!parse_map(map_fd, &map))
		return (do_stuff(cub, map_fd, "Failed to parse map\n"));
	close(map_fd);
	return (true);
}
