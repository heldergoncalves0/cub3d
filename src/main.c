/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:11 by helferna          #+#    #+#             */
/*   Updated: 2024/03/11 19:59:30 by helferna         ###   ########.fr       */
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

	j = 0;
	while (j < cub()->map_height)
	{
		i = 0;
		while (i < cub()->map_width)
		{
			if (ft_strchr("NSWE", cub()->map[j][i]))
			{
				cub()->player.p_x = i;
				cub()->player.p_y = j;
			}
			i++;
		}
		j++;
	}
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
			my_mlx_pixel_put(&cub()->img, i + size_x, j + size_y, color);
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
			int tileX = j * 32;
            int tileY = i * 32;
			if (cub()->map[i][j] == 1)
				draw_square(tileX, tileY, 0XFF0000);
			else
				draw_square(tileX, tileY, 0X000000);
			j++; 
		}
		i++;
	}
}

void	init_cub3d(char **argv)
{
	
	cub()->map_fd = open(argv[1], O_RDWR);
	cub()->map = read_map();
	get_width_heigth();
	find_player_position();
}

int	game_loop(void)
{
	draw_map();
	mlx_put_image_to_window(cub()->mlx, cub()->win, cub()->img.img, 0, 0);
	mlx_destroy_image(cub()->mlx, cub()->img.img);
	return (0);
}

int	handle_input(int keysym)
{
	if (keysym == ESCAPE)
		close_window();
	return (0);
}

void 	run_cub3d(void)
{
	cub()->mlx = mlx_init();
	cub()->win = mlx_new_window(cub()->mlx, 1024, 512, "Cub3d");
	cub()->img.img = mlx_new_image(cub()->mlx, 1024, 512);
	cub()->img.addr = mlx_get_data_addr(cub()->img.img, &cub()->img.bits_per_pixel, &cub()->img.line_length, &cub()->img.endian);
	mlx_loop_hook(cub()->mlx, &game_loop, NULL);
	mlx_hook(cub()->win, 2, 1L << 0, &handle_input, cub());
	//mlx_put_image_to_window(cub()->mlx, cub()->win, cub()->img, 0, 0);
	mlx_loop(cub()->mlx);
}


int	main(int argc, char **argv)
{
	if (!argv[1] || argc > 2 || !verify_path(argv[1]))
	    return (0);
    init_cub3d(argv);
    run_cub3d();
    return (0);
}