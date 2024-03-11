/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:11 by helferna          #+#    #+#             */
/*   Updated: 2024/03/11 16:27:02 by helferna         ###   ########.fr       */
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

char	**read_map()
{
	char	*str;
	char	**map_copied;
	char	*box;
	char	*tmp;

	box = ft_strdup("");
	str = get_next_line(cub()->map_fd);
	while (str)
	{
		tmp = ft_strjoin(box, str);
		free(box);
		free(str);
		box = tmp;
		str = get_next_line(cub()->map_fd);
	}
	free(str);
	map_copied = ft_split(box, '\n');
	if (!map_copied)
	{
		free(box);
		return (NULL);
	}
	free(box);
	close(cub()->map_fd);
	return (map_copied);
}

void	get_width_heigth()
{
	cub()->map_width = ft_strlen(cub()->map[0]);
	while (cub()->map[cub()->map_height] != 0)
		cub()->map_height++;
}

void find_player_position(void)
{
	int i;
	int j;

	i = 0;
	while (i < cub()->map_height)
	{
		j = 0;
		while (j < cub()->map_width)
		{
			if (ft_strchr("NSWE", cub()->map[i][j]))
			{
				cub()->player->p_x = i;
				cub()->player->p_y = j;
			}
			j++;
		}
		i++;
	}
}

void	init_cub3d(char **argv)
{
	
	cub()->map_fd = open(argv[1], O_RDWR);
	cub()->map = read_map();
	find_player_position();
}

void	init_mlx(void)
{
	cub()->mlx = mlx_init();
	cub()->win = mlx_new_window(cub()->mlx, 1024, 512, "Cub3d");
}

void	draw_square(int size_x, int size_y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			mlx_pixel_put(cub()->mlx, cub()->win, i + size_x, j + size_y, color);
			j++;
		}
		i++;
	}
}

void	draw_map(void)
{
	int i;
	int j;

	i = 0;
	while (i < cub()->map_height)
	{
		j = 0;
		while (j < cub()->map_width)
		{
			if (cub()->map[i][j] == 1)
				draw_square(i * 32, j * 32, 0XFF000000);
			else
				draw_square(i * 32, j * 32, 0X00000000);
			j++; 
		}
		i++;
	}
}

void 	run_cub3d(void)
{
	init_mlx();
	draw_map();
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
    init_cub3d(argv);
    run_cub3d();
	mlx_hook(cub()->win, 2, 1L << 0, &handle_input, cub());
	mlx_loop(cub()->mlx);
    return (0);
}