/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:11 by helferna          #+#    #+#             */
/*   Updated: 2024/03/06 17:43:44 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cub	*cub(void)
{
	static t_cub	cub;

	return (&cub);
}

int	verify_path(char *map_path)
{
	int        i;

	if (strlen(map_path) <= 4)
	    return (0);
	if (strncmp(strrchr(map_path, '.'), ".cub", 5) == 0)
        return (1);
	return (0);
}

void	init_cub3d(char **argv)
{
	verify_path(argv[1]);
    cub()->map = copy();
}

void 	run_cub3d(void)
{
	
}

int	main(int argc, char **argv)
{
	if (!argv[1] || argc > 2)
	    return (0);
    init_cub3d(argv);
    run_cub3d();
    return (0);
}