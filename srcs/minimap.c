/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:48:00 by slippert          #+#    #+#             */
/*   Updated: 2023/12/28 15:50:15 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_objects(t_data *data, int is_wall)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == '1' && is_wall)
				mlx_image_to_window(data->mlx, data->img_mm_wall, x * 16, y
					* 16);
			else if ((data->map->map[y][x] == '0'
					|| data->map->map[y][x] == 'P') && is_wall)
				mlx_image_to_window(data->mlx, data->img_mm_wall_shadow, x * 16,
					y * 16);
			else if (data->map->map[y][x] == '5' && is_wall)
			{
				mlx_image_to_window(data->mlx, data->img_mm_door_open, x * 16,
					y * 16);
				data->minimap->doors[y][x] = mlx_image_to_window(data->mlx, data->img_mm_door_closed, x * 16,
					y * 16);
			}
			else if (data->map->map[y][x] == '9' && is_wall)
			{
				mlx_image_to_window(data->mlx, data->img_mm_portal, x * 16,
					y * 16);
			}
			else if (data->map->map[y][x] == 'P' && !is_wall)
				mlx_image_to_window(data->mlx, data->img_player, data->player->x
					* 16, data->player->y * 16);
			x++;
		}
		y++;
	}
}

void	set_z(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->img_mm_wall_shadow->count)
		data->img_mm_wall_shadow->instances[i++].z = 1;
	i = 0;
	while (i < data->img_mm_door_open->count)
		data->img_mm_door_open->instances[i++].z = 1;
	data->img_player->instances[0].z = 2;
}

void	draw_minimap(t_data *data)
{
	int			x;

	draw_objects(data, 0);
	draw_objects(data, 1);
	mlx_image_to_window(data->mlx, data->img_game_cursor, data->width / 2
		- (data->img_game_cursor->width / 2), data->height / 2
		- (data->img_game_cursor->height / 2));
	set_z(data);
}
