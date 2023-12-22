/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2023/12/22 14:45:09 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_for_wall_ahead(t_data *data, float distance, float radianAngle)
{
	float	p_x_cos;
	float	p_y_sin;
	int		cellX;
	int		cellY;

	if (distance > 0)
		distance = 1;
	else
		distance = -1;
	p_x_cos = cos(radianAngle);
	p_y_sin = sin(radianAngle);
	cellX = (int)data->player->x + distance * p_x_cos;
	cellY = (int)data->player->y + distance * p_y_sin;
	if (cellY <= 0 || cellY >= data->map->height - 1 || cellX <= 0
		|| cellX >= data->map->width - 1)
		return (1);
	if (data->map->map[cellY][cellX] == '1')
		return (1);
	return (0);
}

void	move_player(t_data *data, float speed, int forward)
{
	float	radianAngle;
	float	p_x_cos;
	float	p_y_sin;

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

void	update_player_angle(double xpos, double ypos, void *param)
{
	t_data	*data;
	float	deltaX;
	float	deltaY;
	float	newAngle;
	float	sensitivity;
	int		mouseX;
	int		mouseY;

	data = param;
	mlx_get_mouse_pos(data->mlx, &mouseX, &mouseY);
	deltaX = mouseX - data->player->x;
	deltaY = mouseY - data->player->y;
	newAngle = -atan2(deltaY, deltaX) * 180.0 / M_PI;
	sensitivity = 3.0;
	data->player->angle = sensitivity * newAngle;
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
