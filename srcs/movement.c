/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2023/12/29 21:55:19 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_wall_corner_ahead(t_data *data)
{
	int	angle;
	int	x;
	int	y;

	x = data->player->x + 0.5f;
	y = data->player->y + 0.5f;
	angle = (int)data->player->angle;
	printf("angle %d\n", angle % 360);
	printf("x %d y %d\n", x, y);
	if (angle % 360 > 240 && angle % 360 < 360
		&& ft_is_in_set(data->game->map[y][x + 1], "159")
		&& ft_is_in_set(data->game->map[y - 1][x], "159"))
		return (1);
	// else if (angle % 360 > 90 && angle % 360 < 210
	// 	&& (ft_is_in_set(data->game->map[cell_y - 1][cell_x], "159")
	// 	|| ft_is_in_set(data->game->map[cell_y][cell_x + 1], "159")))
	// 	return (1);
	// else if ((angle % 360 > 345 && angle % 360 <= 360) || (angle % 360 >= 0
	//		&& angle % 360 < 105)
	// 		&& (ft_is_in_set(data->game->map[cell_y][cell_x - 1], "159")
	// 		|| ft_is_in_set(data->game->map[cell_y - 1][cell_x + 1], "159")))
	// 	return (1);
	// else if (angle % 360 > 165 && angle % 360 < 285
	// 		&& (ft_is_in_set(data->game->map[cell_y][cell_x + 1], "159")
	// 		|| ft_is_in_set(data->game->map[cell_y + 1][cell_x - 1], "159")))
	// 	return (1);
	return (0);
}

int	check_for_wall_ahead(t_data *data, float distance, float radian_angle)
{
	float	p_x_cos;
	float	p_y_sin;
	float	cell_x;
	float	cell_y;

	p_x_cos = cos(radian_angle);
	p_y_sin = sin(radian_angle);
	cell_y = roundf(data->player->y + distance * p_y_sin);
	cell_x = roundf(data->player->x + distance * p_x_cos);
	if ((cell_y >= 0 && cell_y <= data->game->height && cell_x >= 0
		&& cell_x <= data->game->width)
		&& ft_is_in_set(data->game->map[(int)cell_y][(int)cell_x], "159"))
		return (1);
	return (0);
}

void	move_player(t_data *data, float speed, int forward)
{
	float	radian_angle;
	float	p_x_cos;
	float	p_y_sin;

	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		if (speed > 0)
			speed += 0.15f;
		else
			speed -= 0.15f;
	}
	if (forward == 1)
		radian_angle = data->player->angle * PI / 180.0;
	else
		radian_angle = (data->player->angle + 90.0) * PI / 180.0;
	if (check_for_wall_ahead(data, speed, radian_angle))
		return ;
	// if (check_wall_corner_ahead(data))
	// 	return ;
	p_x_cos = speed * cos(radian_angle);
	p_y_sin = speed * sin(radian_angle);
	data->player->x += p_x_cos;
	data->player->y += p_y_sin;
	data->img->img_player->instances[0].x = data->player->x * 16;
	data->img->img_player->instances[0].y = data->player->y * 16;
}

// Calculate the difference in X position between
// the current and previous mouse position
// Use this difference to update the player's angle
// Update the player's angle
// Save the current mouse position as
// the previous mouse position for the next frame
void	update_player_angle(double xpos, double ypos, void *param)
{
	t_data	*data;
	float	delta_x;
	float	new_angle;
	float	sensitivity;

	data = param;
	mlx_get_mouse_pos(data->mlx, &data->player->mouse_x,
		&data->player->mouse_y);
	delta_x = data->player->mouse_x - data->player->prev_mouseX;
	sensitivity = 0.5;
	new_angle = delta_x * sensitivity;
	data->player->angle += new_angle;
	data->player->prev_mouseX = data->player->mouse_x;
}

void	check_for_door_ahead(t_data *data)
{
	float	p_x_cos;
	float	p_y_sin;
	float	cell_x;
	float	cell_y;
	float	radian_angle;

	radian_angle = data->player->angle * PI / 180.0;
	p_x_cos = cos(radian_angle);
	p_y_sin = sin(radian_angle);
	cell_y = roundf(data->player->y + 1 * p_y_sin);
	cell_x = roundf(data->player->x + 1 * p_x_cos);
	if (cell_y >= 0 && cell_y <= data->game->height && cell_x >= 0
		&& cell_x <= data->game->width)
	{
		if (data->game->map[(int)cell_y][(int)cell_x] == '9')
		{
			data->player->x = data->game->width - 2;
			data->player->y = 1;
			data->img->img_player->instances[0].x = data->player->x * 16;
			data->img->img_player->instances[0].y = data->player->y * 16;
		}
		if (data->game->map[(int)cell_y][(int)cell_x] == '5')
		{
			data->game->map[(int)cell_y][(int)cell_x] = '4';
			data->img->img_mm_door_closed->instances[data->minimap->map[(int)cell_y][(int)cell_x]].enabled = 0;
		}
		else if (data->game->map[(int)cell_y][(int)cell_x] == '4')
		{
			data->game->map[(int)cell_y][(int)cell_x] = '5';
			data->img->img_mm_door_closed->instances[data->minimap->map[(int)cell_y][(int)cell_x]].enabled = 1;
		}
	}
}

void	ft_key_press(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_RELEASE)
		check_for_door_ahead(data);
}

void	ft_key_hold(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		ft_exit(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, 0.05, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -0.05, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, -0.05, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, 0.05, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->angle += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->angle -= 5;
}
