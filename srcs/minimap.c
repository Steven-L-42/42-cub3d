/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:48:00 by slippert          #+#    #+#             */
/*   Updated: 2023/12/23 11:55:10 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	uint32_t	color = ft_pixel(90, 90, 90, 255);
	while (y < data->map->height * 16)
	{
		x = 0;
		while (x < data->map->width * 16)
		{
			mlx_put_pixel(data->img_minimap, x, y, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->img_minimap, 0, 0);
	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->img_game_wall, x * 16, y * 16);
			else if (data->map->map[y][x] == 'P')
				mlx_image_to_window(data->mlx, data->img_player, data->player->x
					* 16, data->player->y * 16);
			x++;
		}
		y++;
	}
}
