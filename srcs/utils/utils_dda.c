/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:01:57 by slippert          #+#    #+#             */
/*   Updated: 2024/01/05 13:47:42 by slippert         ###   ########.fr       */
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
	int	y;
	int	x;

	y = 0;
	while (data->game->map_copy[y] != NULL)
	{
		x = 0;
		while (data->game->map_copy[y][x] != '\0')
		{
			data->game->map_copy[y][x] = data->game->map[y][x];
			x++;
		}
		y++;
	}
}

float	ft_get_block_width(t_calc_view *calc)
{
	int	i;
	int	block_width;

	i = 0;
	block_width = 0;
	while (calc->width_array[i] < calc->j)
	{
		i++;
		if (calc->width_array[i] != (float)0 && calc->width_array[i] < FLT_MAX)
		{
			block_width = (int)calc_for_x(calc->width_array[i]
					- calc->width_array[i - 1], calc->j - calc->width_array[i
					- 1], BLOCK_PIXEL_SIZE);
		}
	}
	return (block_width);
}