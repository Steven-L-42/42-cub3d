/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:01:57 by slippert          #+#    #+#             */
/*   Updated: 2024/01/05 13:15:54 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	calc_for_x(float big, float small, float block_size)
{
	float	x;

	x = fabs(((small) / big) * 64);
	return (x);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	reset_map(t_data *data)
{
	for (int y = 0; data->game->map_copy[y] != NULL; y++)
	{
		for (int x = 0; data->game->map_copy[y][x] != '\0'; x++)
		{
			data->game->map_copy[y][x] = data->game->map[y][x];
		}
	}
}

int	ft_text_color(mlx_texture_t *text, t_calc_view *calc, int block_width,
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