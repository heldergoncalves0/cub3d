/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:11 by helferna          #+#    #+#             */
/*   Updated: 2024/03/11 11:20:22 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	*cub(void)
{
	static t_cub	cub;

	return (&cub);
}

int	verify_path(char *map_path)
{
	if (strlen(map_path) <= 4)
	    return (0);
	if (strncmp(strrchr(map_path, '.'), ".cub", 5) == 0)
        return (1);
	return (0);
}

void	init_cub3d(char **argv)
{
	verify_path(argv[1]);
}
void	init_mlx(void)
{
	cub()->mlx = mlx_init();
	cub()->win = mlx_new_window(cub()->mlx, 1920, 1080, "Cub3d");
}

void 	run_cub3d(void)
{
	init_mlx();
	return ;
}

int	close_window(void)
{
	mlx_destroy_window(cub()->mlx, cub()->win);
	exit (0);
}

int	handle_input(int keysym)
{
	if (keysym == ESCAPE)
		close_window();
	return (0);
}

int	main(int argc, char **argv)
{
	if (!argv[1] || argc > 2 || !verify_path(argv[1]))
	    return (0);
    //init_cub3d(argv);
    run_cub3d();
	mlx_hook(cub()->win, 2, 1L << 0, &handle_input, cub());
	mlx_loop(cub()->mlx);
    return (0);
}