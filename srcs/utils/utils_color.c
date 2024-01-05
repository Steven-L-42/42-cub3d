/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/05 14:23:44 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_text_color(mlx_texture_t *text, t_dda *calc, int block_width,
		int block_height)
{
	int		color;
	int		pos;
	double	brightness;

	pos = (block_height + text->width * block_width) * text->bytes_per_pixel;
	brightness = max(1.0 - (calc->distance / calc->shadow), 0);
	if (calc->distance > calc->shadow)
		return (0x000000ff);
	color = (int)(text->pixels[pos] * brightness) << 24 | (int)(text->pixels[pos
			+ 1] * brightness) << 16 | (int)(text->pixels[pos + 2]
			* brightness) << 8 | (int)text->pixels[pos + 3];
	return (color);
}

uint32_t	ft_select_color(t_data *data, t_dda *calc, int block_height,
		int block_width)
{
	if (data->wall_type == 'W')
	{
		if (calc->direction == 'N')
			calc->color_wall = ft_text_color(data->img->txt_NO, calc,
					block_height, block_width);
		else if (calc->direction == 'E')
			calc->color_wall = ft_text_color(data->img->txt_EA, calc,
					block_height, block_width);
		else if (calc->direction == 'S')
			calc->color_wall = ft_text_color(data->img->txt_SO, calc,
					block_height, block_width);
		else if (calc->direction == 'W')
			calc->color_wall = ft_text_color(data->img->txt_WE, calc,
					block_height, block_width);
	}
	else if (data->wall_type == 'D')
	{
		calc->color_wall = ft_text_color(data->img->txt_door_closed, calc,
				block_height, block_width);
	}
	return (calc->color_wall);
}
