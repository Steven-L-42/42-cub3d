/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:25 by slippert          #+#    #+#             */
/*   Updated: 2023/12/22 15:00:48 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_view(t_data *data)
{
	float		temp1;
	float		temp2;
	int			j;
	int			angle;
	float		height;
	float		tmp;
	float		linehight;
	float		linehight1;
	uint32_t	color;
	static int	testads = 0;

	j = 0;
	temp1 = data->player->view_angle / 2;
	temp2 = -temp1;
	angle = temp1;
	color = ft_pixel(0, 255, 255, 255);
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, data->map->width * SIZE,
			data->map->height * SIZE);
	for (float k = temp2; k < temp1; k++)
	{
		height = ray_distance(data, k);
		for (float i = (data->image->width / data->player->view_angle)
			* j; i < (data->image->width / data->player->view_angle) * (j
				+ 1); ++i)
		{
			tmp = height * cos((angle)*PI / 180);
			linehight = (data->image->height / 2) + (SIZE * 3 / tmp);
			linehight1 = (data->image->height / 2) - (SIZE * 3 / tmp);
			if (linehight1 < 0)
				linehight1 = 0;
			if (linehight >= data->image->height)
				linehight = data->image->height;
			for (int32_t y = data->image->height / 2; y < linehight; y++)
			{
				mlx_put_pixel(data->image, i, y, color);
			}
			for (int32_t y = data->image->height / 2; y > linehight1; y--)
			{
				mlx_put_pixel(data->image, i, y, color);
			}
		}
		angle--;
		j++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
