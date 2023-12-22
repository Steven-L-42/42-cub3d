/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:25 by slippert          #+#    #+#             */
/*   Updated: 2023/12/22 15:46:28 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_view(t_data *data)
{
	float		temp1;
	float		temp2;
	int			j;
	int			angle;
	float		distance;
	t_hit_info	hit_info;
	float		tmp;
	float		linehight;
	float		linehight1;
	uint32_t	color_front;
	uint32_t	color_side;
	int			is_side;

	j = 0;
	temp1 = data->player->view_angle / 2;
	temp2 = -temp1;
	angle = temp1;

	color_front = ft_pixel(0, 255, 255, 255);
	color_side = ft_pixel(0, 100, 255, 255);

	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, data->map->width * SIZE, data->map->height * SIZE);
	for (float k = temp2; k < temp1; k++)
	{
		distance = ray_distance(data, k);

		float i = (data->image->width / data->player->view_angle) * j;
		for (i; i < (data->image->width / data->player->view_angle) * (j+ 1); ++i)
		{

			tmp = distance * cos((angle)*PI / 180);
			linehight = (data->image->height / 2) + (SIZE * 3 / tmp);
			linehight1 = (data->image->height / 2) - (SIZE * 3 / tmp);
			if (linehight1 < 0)
				linehight1 = 0;
			if (linehight >= data->image->height)
				linehight = data->image->height;
			for (int32_t y = data->image->height / 2; y < linehight; y++)
			{
				if (hit_info.hit_side == 1)
					mlx_put_pixel(data->image, i, y, color_front);
				else
					mlx_put_pixel(data->image, i, y, color_side);
			}
			for (int32_t y = data->image->height / 2; y > linehight1; y--)
			{
				if (hit_info.hit_side == 1)
					mlx_put_pixel(data->image, i, y, color_front);
				else
					mlx_put_pixel(data->image, i, y, color_side);
			}
		}
		angle--;
		j++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
