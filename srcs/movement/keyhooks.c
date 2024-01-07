/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2024/01/07 10:26:27 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Calculate the difference in X position between
// the current and previous mouse position
// Use this difference to update the player's angle
// Update the player's angle
// Save the current mouse position as
// the previous mouse position for the next frame
void	ft_player_angle(double xpos, double ypos, void *param)
{
	t_data	*data;
	float	delta_x;
	float	new_angle;
	float	sensitivity;

	xpos = 0;
	ypos = 0;
	data = param;
	mlx_get_mouse_pos(data->mlx, &data->player->mouse_x,
		&data->player->mouse_y);
	delta_x = data->player->mouse_x - data->player->prev_mouseX;
	sensitivity = 0.1;
	new_angle = delta_x * sensitivity;
	data->player->angle += -new_angle;
	data->player->prev_mouseX = data->player->mouse_x;
}

void	ft_key_press(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		check_for_door(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		data->is_shooting = true;
}

void	ft_mouse_press(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_data	*data;

	mods = 0;
	data = param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		data->is_shooting = true;
}

static void	ft_key_hold_helper(t_data *data, const char	*set)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player->dir.sideward = -1;
		move_player(data, 0.05, 0, set);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player->dir.sideward = 1;
		move_player(data, -0.05, 0, set);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->angle -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->angle += 5;
	data->player->dir.forward = 0;
	data->player->dir.sideward = 0;
}

void	ft_key_hold(void *param)
{
	t_data		*data;
	const char	*set = "159";

	data = param;
	data->player->dir.sideward = 0;
	data->player->dir.forward = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		ft_exit(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player->dir.forward = 1;
		move_player(data, 0.05, 1, set);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player->dir.forward = -1;
		move_player(data, -0.05, 1, set);
	}
	ft_key_hold_helper(data, set);
}
