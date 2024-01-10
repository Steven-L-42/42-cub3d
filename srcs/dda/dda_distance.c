/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/10 17:13:06 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	start_dist(float m, float angle, t_vec2 *vec, char *dir, bool *xminus,
		bool *yminus)
{
	float	distx;
	float	disty;
	float	tempx;
	float	tempy;

	disty = 1 - (vec->y - (int)vec->y);
	distx = 1 - (vec->x - (int)vec->x);
	if (angle >= 0 && angle <= 180)
		disty = 1 - disty;
	if (disty == 0)
		disty = 1;
	if (angle >= 90 && angle <= 270)
		distx = 1 - distx;
	if (distx == 0)
		distx = 1;
	distx *= 10;
	disty *= 10;
	if (angle == 0 || angle == 180)
	{
		if (angle >= 90 && angle <= 270)
		{
			*xminus = true;
			vec->x -= distx / 10;
		}
		else
			vec->x += distx / 10;
		return (distx / 10);
	}
	if (angle == 90 || angle == 270)
	{
		if (angle >= 0 && angle <= 180)
		{
			*yminus = true;
			vec->y -= disty / 10;
		}
		else
			vec->y += disty / 10;
		return (disty / 10);
	}
	tempx = (distx * sqrt(1 + pow(m, 2))) / 10;
	tempy = (disty * sqrt(1 + pow(1 / m, 2))) / 10;
	if (m == 0)
		return (tempx);
	if (tempx < tempy)
	{
		if (angle >= 90 && angle <= 270)
		{
			*xminus = true;
			vec->x -= distx / 10;
			*dir = 'W';
		}
		else
		{
			vec->x += distx / 10;
			*dir = 'E';
		}
		if (angle >= 0 && angle <= 180)
		{
			*yminus = true;
			vec->y -= sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		}
		else
			vec->y += sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		return (tempx);
	}
	if (angle >= 0 && angle <= 180)
	{
		*yminus = true;
		vec->y -= disty / 10;
		*dir = 'N';
	}
	else
	{
		vec->y += disty / 10;
		*dir = 'S';
	}
	if (angle >= 90 && angle <= 270)
	{
		*xminus = true;
		vec->x -= sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	}
	else
		vec->x += sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	return (tempy);
}

int	check_for_allocated(char **map, int y, int x)
{
	if (map[y] != NULL && map[y][x] != '\0')
		return (1);
	return (0);
}

float	get_distance(float angle, t_vec2 vec, t_data *data, char *dir,
		bool *new_block)
{
	t_dda_dist	dst;
	static char	old_dir;

	dst.dist = 0;
	dst.tempy = vec.y;
	dst.tempx = vec.x;
	dst.last_dist = dst.dist;
	dst.m = fabs(get_slope(angle));
	while ((data->game->map[dst.tempy] && data->game->map[dst.tempy][dst.tempx] && !ft_is_in_set(data->game->map[dst.tempy][dst.tempx], "159B"))
		|| (data->game->map_copy[dst.tempy] && data->game->map_copy[dst.tempy][dst.tempx] && !ft_is_in_set(data->game->map_copy[dst.tempy][dst.tempx], "159BL")))
	{
		dst.ymin = false;
		dst.xmin = false;
		dst.tempy = vec.y;
		dst.tempx = vec.x;
		dst.last_dist = dst.dist;
		dst.last_dir = *dir;
		if ((!data->game->map[dst.tempy]
				|| !data->game->map[dst.tempy][dst.tempx])
			|| (!data->game->map_copy[dst.tempy]
				|| !data->game->map_copy[dst.tempy][dst.tempx]))
			return (1);
		dst.dist += fabs(start_dist(dst.m, angle, &vec, dir, &dst.xmin,
					&dst.ymin));
		dst.tempy = vec.y;
		dst.tempx = vec.x;
		if (dst.xmin == true && dst.ymin == true)
		{
			dst.tempx = ceil(vec.x) - 1;
			dst.tempy = ceil(vec.y) - 1;
		}
		else
		{
			if (dst.xmin == true)
				dst.tempx = ceil(vec.x) - 1;
			if (dst.ymin == true)
				dst.tempy = ceil(vec.y) - 1;
		}
	}
	if (data->game->map[dst.tempy] && data->game->map[dst.tempy][dst.tempx] &&data->game->map_copy[dst.tempy][dst.tempx] == 'L')
		*new_block = false;
	if (data->game->map[dst.tempy] && data->game->map[dst.tempy][dst.tempx] && ft_is_in_set(data->game->map_copy[dst.tempy][dst.tempx], "159B")
		|| *dir != old_dir)
	{
		data->game->map_copy[dst.tempy][dst.tempx] = 'L';
		*new_block = true;
	}
	if (data->game->map[dst.tempy] && data->game->map[dst.tempy][dst.tempx] && data->game->map[dst.tempy][dst.tempx] == 'B')
		data->wall_type = 'B';
	else if (data->game->map[dst.tempy] && data->game->map[dst.tempy][dst.tempx] && data->game->map[dst.tempy][dst.tempx] == '5')
		data->wall_type = 'D';
	else if (data->game->map[dst.tempy] && data->game->map[dst.tempy][dst.tempx] && data->game->map[dst.tempy][dst.tempx] == '9')
		data->wall_type = 'P';
	else
		data->wall_type = 'W';
	old_dir = *dir;
	return (fabs(dst.dist));
}

float	dda_dist(t_data *data, float angle, char *dir, bool *new_block)
{
	t_vec2	vector;

	vector.x = data->player->x + 0.5f;
	vector.y = data->player->y + 0.5f;
	angle = data->player->angle + angle;
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return (get_distance(angle, vector, data, dir, new_block));
}
