/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:48:00 by slippert          #+#    #+#             */
/*   Updated: 2024/01/11 12:09:01 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_objects_helper(t_data *data, int is_wall, int y, int x)
{
	if (data->game->map[y][x] == '5' && is_wall)
	{
		mlx_image_to_window(data->mlx, data->img->img_mm_door_open, x * 16, y
			* 16);
		data->minimap->map[y][x] = mlx_image_to_window(data->mlx,
				data->img->img_mm_door_closed, x * 16, y * 16);
	}
	else if (data->game->map[y][x] == '9' && is_wall)
		mlx_image_to_window(data->mlx, data->img->img_mm_portal, x * 16, y
			* 16);
	else if (data->game->map[y][x] == 'P' && !is_wall)
		mlx_image_to_window(data->mlx, data->img->img_player, data->player->x
			* 16, data->player->y * 16);
}

static void	draw_objects(t_data *data, int is_wall)
{
	int	x;
	int	y;

	y = 0;
	while (data->game->map[y])
	{
		x = 0;
		while (data->game->map[y][x])
		{
			if (data->game->map[y][x] && data->game->map[y][x] == '1'
				&& is_wall)
				mlx_image_to_window(data->mlx, data->img->img_mm_wall, x * 16, y
					* 16);
			else if (data->game->map[y][x] && (data->game->map[y][x] == '0'
					|| data->game->map[y][x] == 'P') && is_wall)
				mlx_image_to_window(data->mlx, data->img->img_mm_wall_shadow, x
					* 16, y * 16);
			else
				draw_objects_helper(data, is_wall, y, x);
			x++;
		}
		y++;
	}
}

static void	set_z(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->img->img_mm_wall_shadow->count)
		data->img->img_mm_wall_shadow->instances[i++].z = 1;
	i = 0;
	while (i < data->img->img_mm_door_open->count)
		data->img->img_mm_door_open->instances[i++].z = 1;
	data->img->img_player->instances[0].z = 2;
	//data->img->img_movement_ray->instances[0].z = 0;
}

void	ft_draw_overlay(t_data *data)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	color = ft_pixel(45, 45, 45, 255);
	mlx_image_to_window(data->mlx, data->img->img_mm_overlay, 0, 0);
	while (y < data->img->img_mm_overlay->height)
	{
		x = 0;
		while (x < data->img->img_mm_overlay->width)
		{
			mlx_put_pixel(data->img->img_mm_overlay, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *data)
{
	draw_objects(data, 0);
	draw_objects(data, 1);
	ft_draw_overlay(data);
	set_z(data);
}
