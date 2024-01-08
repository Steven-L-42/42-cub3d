/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 21:22:27 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/08 11:14:36 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_shadow_coloring(t_data *data, float t)
{
	double			brightness;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

	if (t + 25 > 512)
		return (ft_pixel(0, 0, 0, 255));
	brightness = 1.0f - (float)(t) / 512;
	r = (data->game->color_ceiling >> 24) & 0xFF;
	g = (data->game->color_ceiling >> 16) & 0xFF;
	b = (data->game->color_ceiling >> 8) & 0xFF;
	a = data->game->color_ceiling & 0xFF;
	r = r * brightness;
	g = g * brightness;
	b = b * brightness;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	draw_floor_ceiling(t_data *data, t_dda *dda)
{
	float	t;
	int		color;

	t = -1;
	while (++t < dda->line_top)
	{
		if (data->is_shooting)
			color = ft_pixel(255, 255, 255, 255);
		else
			color = ft_shadow_coloring(data, t);
		mlx_put_pixel(data->img->img_game, dda->j, t, color);
	}
	t = dda->line_bottom - 1;
	while (++t < data->height)
		mlx_put_pixel(data->img->img_game, dda->x, t, data->game->color_floor);
}

void	draw_wall(t_data *data, t_dda *dda, int block_width, float y)
{
	float	block_height;

	while (y < dda->line_bottom)
	{
		block_height = calc_for_x(dda->line_bottom - dda->line_top, y
				- dda->line_top);
		dda->color_wall = ft_select_color(data, dda, block_height, block_width);
		mlx_put_pixel(data->img->img_game, dda->j, y, dda->color_wall);
		y++;
	}
}

void	draw_vertical(t_data *data, t_dda *dda, bool if_true, int block_width)
{
	float			y;
	static float	temp_if_true;

	dda->tmp = round(dda->distance * cos((dda->angle) * PI / 180) * 1000)
		/ 1000;
	if (if_true == true && temp_if_true < dda->tmp)
		dda->tmp = temp_if_true;
	dda->line_bottom = (data->height / 2) + (SIZE * dda->treshold / dda->tmp);
	dda->line_top = (data->height / 2) - (SIZE * dda->treshold / dda->tmp);
	if (dda->line_top < 0)
		dda->line_top = 0;
	if (dda->line_bottom >= data->height)
		dda->line_bottom = data->height;
	y = dda->line_top;
	draw_wall(data, dda, block_width, y);
	draw_floor_ceiling(data, dda);
	temp_if_true = dda->tmp;
}

void	dda_vertical(t_data *data, t_dda *dda, bool if_true)
{
	int	x_dir;
	int	block_width;

	x_dir = 0;
	block_width = ft_get_block_width(dda);
	while (x_dir < QUALITY)
	{
		draw_vertical(data, dda, if_true, block_width);
		x_dir++;
		if (x_dir < QUALITY)
			dda->j++;
	}
}
