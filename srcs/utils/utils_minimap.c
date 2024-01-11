/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/11 14:45:30 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_set_explored_string(t_data *data)
{
	char	*test;
	char	*percent;

	if (data->game->curr_explored >= 75)
		data->game->curr_explored = 100;
	if (data->img->img_mm_explored)
		mlx_delete_image(data->mlx, data->img->img_mm_explored);
	percent = ft_itoa(data->game->curr_explored);
	test = ft_strjoin(percent, " \% explored");
	data->img->img_mm_explored = mlx_put_string(data->mlx, (const char *)test,
			0, 0);
	free(test);
	free(percent);
}

void	ft_check_is_explored(t_data *data)
{
	uint32_t	max;
	int			start;
	uint32_t	count;
	int			color;

	color = ft_pixel(0, 0, 0, 0);
	max = data->img->img_mm_overlay->width * data->img->img_mm_overlay->height
		* sizeof(uint32_t);
	start = 0;
	count = 0;
	while (start < max)
	{
		if (data->img->img_mm_overlay->pixels[start] == color)
			count++;
		start++;
	}
	data->game->curr_explored = (count * 100.0) / max;
	if (count >= 0.75 * max)
	{
		ft_memset(data->img->img_mm_overlay->pixels, 0,
			data->img->img_mm_overlay->width * data->img->img_mm_overlay->height
			* sizeof(uint32_t));
		data->game->is_explored = true;
	}
	ft_set_explored_string(data);
}

void	draw_map_explored(t_data *data, int r, int x, int y)
{
	int		x_middle;
	int		y_middle;
	int		radius;
	double	angle;
	int		color;

	x_middle = data->player->x * 16 + 6;
	y_middle = data->player->y * 16 + 6;
	radius = 50;
	angle = 0;
	color = ft_pixel(0, 0, 0, 0);
	while (angle <= 2 * M_PI)
	{
		r = 0;
		while (r <= radius)
		{
			x = x_middle + (int)(r * cos(angle));
			y = y_middle + (int)(r * sin(angle));
			if (x >= 0 && y >= 0 && x < data->img->img_mm_overlay->width
				&& y < data->img->img_mm_overlay->height)
				mlx_put_pixel(data->img->img_mm_overlay, x, y, color);
			++r;
		}
		angle += 0.01;
	}
}
