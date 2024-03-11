/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:13:47 by helferna          #+#    #+#             */
/*   Updated: 2024/03/11 11:17:53 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/X.h>
# endif

# ifdef __linux__
#  define ESCAPE 65307
#  define W 119
#  define S 115
#  define A 97
#  define D 100
#  define LEFT 65361
#  define RIGHT 65363
#  define UP 65362
#  define DOWN 65364
# endif

typedef struct    s_cub3d{
	void	*mlx;
	void	*win;
	char	**map;
}	t_cub;

t_cub	*cub(void);