/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2023/12/25 13:26:09 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_for_wall_ahead(t_data *data, float distance, float radianAngle)
{
	float	p_x_cos;
	float	p_y_sin;
	float	cellX;
	float	cellY;

	p_x_cos = cos(radianAngle);
	p_y_sin = sin(radianAngle);
	cellX = (data->player->x + distance * p_x_cos);
	cellY = (data->player->y + distance * p_y_sin);
	cellY = roundf(cellY);
	cellX = roundf(cellX);
	if (cellY >= 0 && cellY <= data->map->height && cellX >= 0
		&& cellX <= data->map->width)
	{
		if (data->map->map[(int)cellY][(int)cellX] == '1')
			return (1);
	}
	return (0);
}

void	move_player(t_data *data, float speed, int forward)
{
	float	radianAngle;
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
		radianAngle = data->player->angle * PI / 180.0;
	else
		radianAngle = (data->player->angle + 90.0) * PI / 180.0;
	if (check_for_wall_ahead(data, speed, radianAngle))
		return ;
	p_x_cos = speed * cos(radianAngle);
	p_y_sin = speed * sin(radianAngle);
	data->player->x += p_x_cos;
	data->player->y += p_y_sin;
	data->img_player->instances[0].x = data->player->x * 16;
	data->img_player->instances[0].y = data->player->y * 16;
}

// Calculate the difference in X position between the current and previous mouse position
// Use this difference to update the player's angle
// Update the player's angle
// Save the current mouse position as the previous mouse position for the next frame
void	update_player_angle(double xpos, double ypos, void *param)
{
	t_data	*data;
	float	deltaX;
	float	newAngle;
	float	sensitivity;

	data = param;
	mlx_get_mouse_pos(data->mlx, &data->player->mouse_x,
		&data->player->mouse_y);
	deltaX = data->player->mouse_x - data->player->prev_mouseX;
	sensitivity = 0.5;
	newAngle = deltaX * sensitivity;
	data->player->angle += newAngle;
	data->player->prev_mouseX = data->player->mouse_x;
}
void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(data->mlx, data->image);
		ft_exit(data);
	}
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
