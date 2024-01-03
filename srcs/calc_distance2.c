/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:39:56 by slippert          #+#    #+#             */
/*   Updated: 2024/01/03 14:11:39 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 21:05:04 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/30 16:26:16 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	get_slope(float angle)
{
	float	radianAngle;
	float	dirx;
	float	diry;

	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	if (angle == 90)
		return (INT32_MAX);
	if (angle == 270)
		return (INT32_MIN);
	radianAngle = (angle)*PI / 180.0;
	dirx = cos(radianAngle);
	diry = sin(radianAngle);
	return (diry / dirx);
}

int	aufrunden(float num)
{
	float	temp;

	if (num >= 0)
	{
		temp = num - (int)num;
		if (temp == 0)
			return (num);
		temp = 1 - temp;
		return (num + temp);
	}
	num = fabs(num);
	temp = num - (int)num;
	if (temp == 0)
		return (-num);
	temp = 1 - temp;
	return (-(num + temp));
}

float	startdist(float m, float angle, float *playerx, float *playery,
		char *dir, bool *xminus, bool *yminus)
{
	float	distx;
	float	disty;
	float	tempx;
	float	tempy;

	disty = 1 - (*playery - (int)*playery);
	distx = 1 - (*playerx - (int)*playerx);
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
			*playerx -= distx / 10;
		}
		else
			*playerx += distx / 10;
		return (distx / 10);
	}
	if (angle == 90 || angle == 270)
	{
		if (angle >= 0 && angle <= 180)
		{
			*yminus = true;
			*playery -= disty / 10;
		}
		else
			*playery += disty / 10;
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
			*playerx -= distx / 10;
		}
		else
			*playerx += distx / 10;
		if (angle >= 0 && angle <= 180)
		{
			*yminus = true;
			*playery -= sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		}
		else
			*playery += sqrt(pow(tempx, 2) - pow((distx / 10), 2));
		*dir = 'x';
		return (tempx);
	}
	if (angle >= 0 && angle <= 180)
	{
		*yminus = true;
		*playery -= disty / 10;
	}
	else
		*playery += disty / 10;
	if (angle >= 90 && angle <= 270)
	{
		*xminus = true;
		*playerx -= sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	}
	else
		*playerx += sqrt(pow(tempy, 2) - pow((disty / 10), 2));
	*dir = 'y';
	return (tempy);
}

float	calc_distance(float angle, float playerx, float playery, t_data *data,
		char *dir)
{
	float	dist;
	int		tempy;
	int		tempx;
	float	last_dist;
	float	m;
	char	last_dir;
	bool	xmin;
	bool	ymin;

	dist = 0;
	tempy = playery;
	tempx = playerx;
	last_dist = dist;
	xmin = false;
	ymin = false;
	m = fabs(get_slope(angle));
	while (!ft_is_in_set(data->game->map[tempy][tempx], "159"))
	{
		ymin = false;
		xmin = false;
		tempy = playery;
		tempx = playerx;
		last_dist = dist;
		last_dir = *dir;
		if (!data->game->map[tempy][tempx] || !data->game->map[tempy])
			return (1);
		dist += fabs(startdist(m, angle, &playerx, &playery, dir, &xmin,
					&ymin));
		tempy = playery;
		tempx = playerx;
		if (xmin == true && ymin == true)
		{
			tempx = aufrunden(playerx) - 1;
			tempy = aufrunden(playery) - 1;
		}
		else
		{
			if (xmin == true)
				tempx = aufrunden(playerx) - 1;
			if (ymin == true)
				tempy = aufrunden(playery) - 1;
		}
	}
	if (data->game->map[tempy][tempx] == '5')
		data->wall_type = 'D';
	else if (data->game->map[tempy][tempx] == '9')
		data->wall_type = 'P';
	return (fabs(dist));
}

float	calc_dist(t_data *data, float angle, char *dir)
{
	float playerx = data->player->x + 0.5f;
	float playery = data->player->y + 0.5f;

	angle = data->player->angle + angle;
	while (angle >= 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return (calc_distance(angle, playerx, playery, data, dir));
}