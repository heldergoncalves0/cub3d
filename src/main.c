/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:11 by helferna          #+#    #+#             */
/*   Updated: 2024/03/12 13:02:00 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verify_path(char *map_path)
{
	if (strlen(map_path) <= 4)
	    return (0);
	if (strncmp(strrchr(map_path, '.'), ".cub", 5) == 0)
        return (1);
	return (0);
}

void	get_width_heigth(t_cub *cub)
{
	cub->map_width = ft_strlen(cub->map[0]);
	while (cub->map[cub->map_height] != 0)
		cub->map_height++;
}

void find_player_position(t_cub *cub)
{
	int i;
	int j;

	j = 0;
	while (j < cub->map_height)
	{
		i = 0;
		while (i < cub->map_width)
		{
			if (ft_strchr("NSWE", cub->map[j][i]))
			{
				cub->player.p_x = i;
				cub->player.p_y = j;
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

// void	img_pix_put(t_image *img, int x, int y, int color)
// {
//     char    *pixel;
//     int		i;

//     i = img->bits_per_pixel - 8;
//     pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
//     while (i >= 0)
//     {
//         /* big endian, MSB is the leftmost bit */
//         if (img->endian != 0)
//             *pixel++ = (color >> i) & 0xFF;
//         /* little endian, LSB is the leftmost bit */
//         else
//             *pixel++ = (color >> (img->bits_per_pixel - 8 - i)) & 0xFF;
//         i -= 8;
//     }
// }

void	draw_square(t_image *img, int size_x, int size_y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			// printf("test: %d %d\n", i + size_x, j + size_y);
			my_mlx_pixel_put(img, i + size_x, j + size_y, color);
			// img_pix_put(img, j + size_x, i + size_y, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (j < cub->map_width)
		{
			int tileX = j * 32;
            int tileY = i * 32;
			if (cub->map[i][j] == '1')
				draw_square(&cub->img, tileX, tileY, 0XFF0000);
			else
				draw_square(&cub->img, tileX, tileY, 0X000000);
			j++; 
		}
		i++;
	}
}

void	init_cub3d(t_cub *cub, char **argv)
{
	cub->map_fd = open(argv[1], O_RDWR);
	cub->map = read_map(cub);
	get_width_heigth(cub);
	find_player_position(cub);
}

static int	game_loop(t_cub *cub)
{
	draw_map(cub);
	//my_mlx_pixel_put(&cub->img, 1, 1, 0XFF0000);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (0);
}

static int	handle_input(int keysym, t_cub *cub)
{
	if (keysym == ESCAPE)
		close_window(cub);
	return (0);
}

void	run_cub3d(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, 1024, 512, "CUB3D");
	cub->img.img = mlx_new_image(cub->mlx, 1024, 512);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, \
										&cub->img.line_length, &cub->img.endian);
	// game_loop(cub);
	mlx_loop_hook(cub->mlx, &game_loop, cub);
	//mlx_key_hook(cub->mlx, &handle_input, &cub);
	mlx_loop(cub->mlx);
	//mlx_destroy_image(cub->mlx, cub->img.img);
	//mlx_destroy_window(cub->mlx, cub->win);
	//free(cub->mlx);
}


int	main(int argc, char **argv)
{
	static t_cub cub;

 	if (!argv[1] || argc > 2 || !verify_path(argv[1]))
 	    return (0);
	init_cub3d(&cub, argv);
    run_cub3d(&cub);
    return (0);
}
