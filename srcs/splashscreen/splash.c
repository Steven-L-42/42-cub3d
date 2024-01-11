/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:44:13 by slippert          #+#    #+#             */
/*   Updated: 2024/01/11 18:50:50 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_open_image_splash(t_data *data)
{
	ft_open_image(data, &data->img->img_splash,
		"textures/splash/splash_main.png");
	ft_open_image(data, &data->img->img_splash_random,
		"textures/splash/splash_random.png");
	ft_open_image(data, &data->img->img_splash_normal,
		"textures/splash/splash_normal.png");
}

void	ft_splash_to_game(t_data *data)
{
	data->is_started = true;
	data->img->img_splash->instances->enabled = false;
	data->img->img_splash_normal->instances->enabled = false;
	data->img->img_splash_random->instances->enabled = false;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
}

void	ft_start_game(t_data *data)
{
	if (data->player->mouse_y >= 450 && data->player->mouse_y <= 520)
	{
		data->img->img_splash_normal->instances->enabled = true;
		data->img->img_splash_random->instances->enabled = false;
		data->img->img_splash->instances->enabled = false;
	}
	else if (data->player->mouse_y >= 620 && data->player->mouse_y <= 690)
	{
		data->img->img_splash_random->instances->enabled = true;
		data->img->img_splash_normal->instances->enabled = false;
		data->img->img_splash->instances->enabled = false;
	}
	else
	{
		data->img->img_splash->instances->enabled = true;
		data->img->img_splash_normal->instances->enabled = false;
		data->img->img_splash_random->instances->enabled = false;
	}
}
