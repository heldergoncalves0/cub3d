/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:01:46 by helferna          #+#    #+#             */
/*   Updated: 2024/03/12 11:27:25 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_map(t_cub *cub)
{
	char	*str;
	char	**map_copied;
	char	*box;
	char	*tmp;

	box = ft_strdup("");
	str = get_next_line(cub->map_fd);
	while (str)
	{
		tmp = ft_strjoin(box, str);
		free(box);
		free(str);
		box = tmp;
		str = get_next_line(cub->map_fd);
	}
	free(str);
	map_copied = ft_split(box, '\n', 0);
	if (!map_copied)
	{
		free(box);
		return (NULL);
	}
	free(box);
	close(cub->map_fd);
	return (map_copied);
}
