/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/08 16:04:20 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	ft_shadow_coloring(t_data *data, float start, int src_color,
		bool is_floor)
{
	double			brightness;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

	if (!data->is_shooting && ((is_floor && start - 30 < 512) || (!is_floor
				&& start + 30 > 512)))
		return (ft_pixel(0, 0, 0, 255));
	if (is_floor)
		brightness = -((float)(512 - start) / 512);
	else
		brightness = 1.0f - (float)(start) / 512;
	if (data->is_shooting)
		brightness = 1;
	r = (src_color >> 24) & 0xFF;
	g = (src_color >> 16) & 0xFF;
	b = (src_color >> 8) & 0xFF;
	a = src_color & 0xFF;
	r = r * brightness;
	g = g * brightness;
	b = b * brightness;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static int	ft_text_color(mlx_texture_t *text, t_dda *dda, int block_width,
		int block_height)
{
	int		color;
	int		pos;
	double	brightness;

	pos = text->bytes_per_pixel * (block_height + text->width * block_width);
	brightness = ft_max(1.0 - (dda->distance / dda->shadow), 0);
	if (dda->distance > dda->shadow)
		return (255);
	color = (int)(text->pixels[pos] * brightness) << 24 | (int)(text->pixels[pos
			+ 1] * brightness) << 16 | (int)(text->pixels[pos + 2]
			* brightness) << 8 | (int)text->pixels[pos + 3];
	return (color);
}

uint32_t	ft_select_color(t_data *data, t_dda *dda, int block_height,
		int block_width)
{
	if (data->is_shooting)
		dda->shadow = 100;
	if (data->wall_type == 'W')
	{
		if (dda->direction == 'N')
			dda->color_wall = ft_text_color(data->img->txt_NO, dda,
					block_height, block_width);
		else if (dda->direction == 'E')
			dda->color_wall = ft_text_color(data->img->txt_EA, dda,
					block_height, block_width);
		else if (dda->direction == 'S')
			dda->color_wall = ft_text_color(data->img->txt_SO, dda,
					block_height, block_width);
		else if (dda->direction == 'W')
			dda->color_wall = ft_text_color(data->img->txt_WE, dda,
					block_height, block_width);
	}
	else if (data->wall_type == 'D')
	{
		dda->color_wall = ft_text_color(data->img->txt_door_closed, dda,
				block_height, block_width);
	}
	return (dda->color_wall);
}
