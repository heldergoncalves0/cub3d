/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:00:07 by helferna          #+#    #+#             */
/*   Updated: 2024/09/12 09:51:22 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	_check_for_colision(t_player *player, char **map, t_vector dir)
{
	t_vector	collision;

	collision = (t_vector){0, 0};
	if (dir.x > 0)
		collision.x = 0.1;
	else if (dir.x < 0)
		collision.x = -0.1;
	if (dir.y > 0)
		collision.y = 0.1;
	else if (dir.y < 0)
		collision.y = -0.1;
	if (map[(int)(player->pos.y)][(int)(player->pos.x + dir.x
			+ collision.x)] == '0')
		player->pos.x += dir.x;
	if (map[(int)(player->pos.y + dir.y
			+ collision.y)][(int)(player->pos.x)] == '0')
		player->pos.y += dir.y;
}

void	rotate_vector(t_vector *vec, double angle)
{
	double		rad;
	t_vector	tmp;

	rad = angle * M_PI / 180;
	tmp = (t_vector){.x = vec->x, .y = vec->y};
	vec->x = tmp.x * cos(rad) - tmp.y * sin(rad);
	vec->y = tmp.x * sin(rad) + tmp.y * cos(rad);
}

void	rotate_player_dir(t_vector *vector, t_vector *rotate)
{
	double		theta;
	t_vector	tmp;

	theta = atan2(rotate->y, rotate->x) + M_PI / 2;
	tmp = (t_vector){.x = vector->x, .y = vector->y};
	vector->x = tmp.x * cos(theta) + tmp.y * -sin(theta);
	vector->y = -tmp.x * -sin(theta) + tmp.y * cos(theta);
}

void	_get_vec_magnitude(t_vector *vector)
{
	double	length;

	length = sqrt((vector->x * vector->x) + (vector->y * vector->y));
	vector->x /= length;
	vector->y /= length;
}

void	player_move(t_player *player, t_controller *controller, char **map)
{
	t_vector	move_dir;

	move_dir = (t_vector){0, 0};
	move_dir.y -= controller->mv_fw;
	move_dir.y += controller->mv_bw;
	move_dir.x -= controller->mv_lf;
	move_dir.x += controller->mv_rt;
	if (controller->rt_lf)
		rotate_vector(&player->dir, -1);
	if (controller->rt_rt)
		rotate_vector(&player->dir, 1);
	if (move_dir.x == 0 && move_dir.y == 0)
		return ;
	if (controller->speed < 1)
		controller->speed = 1;
	rotate_player_dir(&move_dir, &player->dir);
	move_dir.x *= 0.009 * controller->speed;
	move_dir.y *= 0.009 * controller->speed;
	_check_for_colision(player, map, move_dir);
	_get_vec_magnitude(&player->dir);
}
