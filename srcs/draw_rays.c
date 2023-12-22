/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:49:49 by slippert          #+#    #+#             */
/*   Updated: 2023/12/22 14:50:01 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_player_rays(t_data *data, int num_rays)
{
	uint32_t	color;
	float		angle_offset;
	float		end_x;
	float		end_y;
	int			x_coord;
	int			y_coord;

	ft_memset(data->img_player_ray->pixels, 0, data->img_player_ray->width
		* data->img_player_ray->height * sizeof(int32_t));
	color = ft_pixel(0, 255, 128, 255);
	for (int i = -num_rays / 2; i <= num_rays / 2; i++)
	{
		angle_offset = i;
		end_x = data->player->x * 16 + 8 * cos((data->player->angle
					+ angle_offset) * PI / 180);
		end_y = data->player->y * 16 + 8 * sin((data->player->angle
					+ angle_offset) * PI / 180);
		for (int j = 0; j < INT_MAX / 2; j++)
		{
			x_coord = data->player->x * 16 + 8 + j * cos((data->player->angle
						+ angle_offset) * PI / 180);
			y_coord = data->player->y * 16 + 8 + j * sin((data->player->angle
						+ angle_offset) * PI / 180);
			if (x_coord >= 0 && y_coord >= 0
				&& x_coord < data->img_player_ray->width
				&& y_coord < data->img_player_ray->height)
			{
				if (data->map->map[y_coord / 16][x_coord / 16] == '1')
					break ;
				mlx_put_pixel(data->img_player_ray, x_coord, y_coord, color);
			}
		}
	}
	mlx_image_to_window(data->mlx, data->img_player_ray, 0, 0);
}
