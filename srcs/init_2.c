/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2023/12/30 13:49:19 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_img_two(t_data *data)
{
	if (ft_open_image(data, &data->img->img_game_cursor, "textures/cross.png", 0))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_wall, "textures/brick_small.png", 0))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_portal, "textures/brick_portal_small.png", 0))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_door_closed, "textures/brick_door_closed_small.png", 0))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_door_open, "textures/brick_door_open_small.png", 0))
		return (1);
	if (ft_open_image(data, &data->img->img_mm_wall_shadow, "textures/brick_shadow_small.png", 0))
		return (1);
	if (ft_open_image(data, &data->img->img_player, "textures/player.png", 0))
		return (1);
	return (0);
}

int	init_img_one(t_data *data)
{
	if (ft_open_image(data, &data->img->img_NO, data->game->NO, 1))
		return (1);
	if (ft_open_image(data, &data->img->img_SO, data->game->SO, 1))
		return (1);
	if (ft_open_image(data, &data->img->img_WE, data->game->WE, 1))
		return (1);
	if (ft_open_image(data, &data->img->img_EA, data->game->EA, 1))
		return (1);
	return (0);
}

void	init_coords(t_data *data, int pixel_x, int pixel_y)
{
	int	i;
	int	j;

	i = 0;
	while (data->game->map[i])
	{
		j = 0;
		while (data->game->map[i][j])
		{
			if (data->game->map[i][j] == 'N' || data->game->map[i][j] == 'E'
				|| data->game->map[i][j] == 'S' || data->game->map[i][j] == 'W')
			{
				data->player->start_direction = data->game->map[i][j];
				data->game->map[i][j] = 'P';
				data->player->x = pixel_x;
				data->player->y = pixel_y;
				return ;
			}
			pixel_x += 1;
			j++;
		}
		pixel_x = 0;
		pixel_y += 1;
		i++;
	}
}

void	init_player(t_data *data)
{
	if (data->player->start_direction == 'N')
		data->player->angle = 270;
	if (data->player->start_direction == 'E')
		data->player->angle = 0;
	if (data->player->start_direction == 'S')
		data->player->angle = 90;
	if (data->player->start_direction == 'W')
		data->player->angle = 180;
	data->player->view_angle = 80;
	data->player->prev_mouseX = 0;
}
