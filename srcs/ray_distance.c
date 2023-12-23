/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:45:14 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/23 11:08:06 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	calculate_distance_to_wall(t_data *data, float dirX, float dirY)
{
	float	stepSize;
	float	distance;
	float	currentX;
	float	currentY;

	stepSize = 0.001;
	currentX = data->player->x;
	currentY = data->player->y;
	while (data->map->map[(int)currentY][(int)currentX] != '1')
	{
		if (data->map->map[(int)currentY][(int)currentX] == '\0'
			|| data->map->map[(int)currentY] == NULL)
			return (-1);
		currentX += stepSize * dirX;
		currentY += stepSize * dirY;
	}
	distance = sqrt((currentX - data->player->x) * (currentX - data->player->x)
			+ (currentY - data->player->y) * (currentY - data->player->y));
	return (distance);
}

void	calculate_direction(float angle, float dir[2])
{
	float	radianAngle;

	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	radianAngle = (angle)*PI / 180.0;
	dir[0] = cos(radianAngle);
	dir[1] = sin(radianAngle);
}

float	ray_distance(t_data *data, float angle)
{
	float	dir[2];

	calculate_direction(data->player->angle + angle, dir);
	return (calculate_distance_to_wall(data, dir[0], dir[1]));
}
