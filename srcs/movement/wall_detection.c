/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2024/01/05 14:23:44 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_wall_corner_ahead(t_data *data, const char *set)
{
	data->detc.x = data->player->x + 0.5f;
	data->detc.y = data->player->y + 0.5f;
	data->detc.angle = (int)data->player->angle;
	if (((data->detc.angle % 360 > -270 && data->detc.angle % 360 < -180)
			|| (data->detc.angle % 360 > 90 && data->detc.angle % 360 < 180))
		&& ft_is_in_set(data->game->map[data->detc.y][data->detc.x - 1], set)
		&& ft_is_in_set(data->game->map[data->detc.y - 1][data->detc.x], set))
		return (1);
	else if (((data->detc.angle % 360 > 180 && data->detc.angle % 360 < 270)
			|| (data->detc.angle % 360 > -180 && data->detc.angle % 360 < -90))
		&& ft_is_in_set(data->game->map[data->detc.y][data->detc.x - 1], set)
		&& ft_is_in_set(data->game->map[data->detc.y + 1][data->detc.x], set))
		return (1);
	else if (((data->detc.angle % 360 > -360 && data->detc.angle % 360 < -270)
			|| (data->detc.angle % 360 > 0 && data->detc.angle % 360 < 90))
		&& (ft_is_in_set(data->game->map[data->detc.y][data->detc.x + 1], set)
		&& ft_is_in_set(data->game->map[data->detc.y - 1][data->detc.x], set)))
		return (1);
	else if (((data->detc.angle % 360 > 270 && data->detc.angle % 360 < 360)
			|| (data->detc.angle % 360 > -90 && data->detc.angle % 360 < 0))
		&& (ft_is_in_set(data->game->map[data->detc.y][data->detc.x + 1], set)
		&& ft_is_in_set(data->game->map[data->detc.y + 1][data->detc.x], set)))
		return (1);
	return (0);
}

// ft_printf("Angle %d\n", angle % 360);
// ft_printf("x %d y %d\n\n", x, y);
int	check_wall_corner_behind(t_data *data, const char *set)
{
	data->detc.x = data->player->x + 0.5f;
	data->detc.y = data->player->y + 0.5f;
	data->detc.angle = (int)data->player->angle;
	if (((data->detc.angle % 360 > -90 && data->detc.angle % 360 < 0)
			|| (data->detc.angle % 360 > 270 && data->detc.angle % 360 < 360))
		&& ft_is_in_set(data->game->map[data->detc.y][data->detc.x - 1], set)
		&& ft_is_in_set(data->game->map[data->detc.y - 1][data->detc.x], set))
		return (1);
	else if (((data->detc.angle % 360 > 0 && data->detc.angle % 360 < 90)
			|| (data->detc.angle % 360 > -360 && data->detc.angle % 360 < -270))
		&& ft_is_in_set(data->game->map[data->detc.y][data->detc.x - 1], set)
		&& ft_is_in_set(data->game->map[data->detc.y + 1][data->detc.x], set))
		return (1);
	else if (((data->detc.angle % 360 > -180 && data->detc.angle % 360 < -90)
			|| (data->detc.angle % 360 > 180 && data->detc.angle % 360 < 270))
		&& (ft_is_in_set(data->game->map[data->detc.y][data->detc.x + 1], set)
		&& ft_is_in_set(data->game->map[data->detc.y - 1][data->detc.x], set)))
		return (1);
	else if (((data->detc.angle % 360 > 90 && data->detc.angle % 360 < 180)
			|| (data->detc.angle % 360 > -270 && data->detc.angle % 360 < -180))
		&& (ft_is_in_set(data->game->map[data->detc.y][data->detc.x + 1], set)
		&& ft_is_in_set(data->game->map[data->detc.y + 1][data->detc.x], set)))
		return (1);
	return (0);
}

int	check_for_wall(t_data *data, float distance, float radian_angle,
		const char *set)
{
	float	p_x_cos;
	float	p_y_sin;
	float	cell_x;
	float	cell_y;

	p_x_cos = cos(radian_angle);
	p_y_sin = sin(radian_angle);
	cell_y = roundf(data->player->y - distance * p_y_sin);
	cell_x = roundf(data->player->x + distance * p_x_cos);
	if ((cell_y >= 0 && cell_y <= data->game->height && cell_x >= 0
			&& cell_x <= data->game->width)
		&& ft_is_in_set(data->game->map[(int)cell_y][(int)cell_x], set))
		return (1);
	return (0);
}

int	check_for_door_preset(t_data *data, t_check_door *door)
{
	door->radian_angle = data->player->angle * PI / 180.0;
	door->p_x_cos = cos(door->radian_angle);
	door->p_y_sin = sin(door->radian_angle);
	door->cell_y = roundf(data->player->y - 1 * door->p_y_sin);
	door->cell_x = roundf(data->player->x + 1 * door->p_x_cos);
	if (door->cell_y >= 0 && door->cell_y <= data->game->height
		&& door->cell_x >= 0 && door->cell_x <= data->game->width)
	{
		door->instance
			= data->minimap->map[(int)door->cell_y][(int)door->cell_x];
		return (door->instance);
	}
	return (-1);
}

void	check_for_door(t_data *data)
{
	t_check_door	door;

	if (check_for_door_preset(data, &door) == -1)
		return ;
	if (data->game->map[(int)door.cell_y][(int)door.cell_x] == '9')
	{
		data->player->x = data->game->width / 2;
		data->player->y = data->game->height / 2;
		data->img->img_player->instances[0].x = data->player->x * 16;
		data->img->img_player->instances[0].y = data->player->y * 16;
	}
	if (data->game->map[(int)door.cell_y][(int)door.cell_x] == '5')
	{
		data->game->map[(int)door.cell_y][(int)door.cell_x] = '4';
		data->img->img_mm_door_closed->instances[door.instance].enabled = 0;
	}
	else if (data->game->map[(int)door.cell_y][(int)door.cell_x] == '4')
	{
		data->game->map[(int)door.cell_y][(int)door.cell_x] = '5';
		data->img->img_mm_door_closed->instances[door.instance].enabled = 1;
	}
}
