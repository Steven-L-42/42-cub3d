/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 21:22:27 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/05 13:45:00 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_floor_ceiling(t_data *data, t_calc_view *calc)
{
	float	t;

	t = -1;
	while (++t < calc->line_top)
		mlx_put_pixel(data->img->img_game, calc->j, t,
			data->game->color_ceiling);
	t = calc->line_bottom - 1;
	while (++t < data->height)
		mlx_put_pixel(data->img->img_game, calc->x, t, data->game->color_floor);
}

void	draw_wall(t_data *data, t_calc_view *calc, int block_width, float y)
{
	float	block_height;

	while (y < calc->line_bottom)
	{
		block_height = calc_for_x(calc->line_bottom - calc->line_top, y
				- calc->line_top, BLOCK_PIXEL_SIZE);
		calc->color_wall = ft_select_color(data, calc, block_height,
				block_width);
		mlx_put_pixel(data->img->img_game, calc->j, y, calc->color_wall);
		y++;
	}
}

void	draw_vertical(t_data *data, t_calc_view *calc, bool if_true,
		int block_width)
{
	float			y;
	float			t;
	static float	temp_if_true;

	calc->tmp = round(calc->distance * cos((calc->angle) * PI / 180) * 1000)
		/ 1000;
	if (if_true == true && temp_if_true < calc->tmp)
		calc->tmp = temp_if_true;
	calc->line_bottom = (data->height / 2) + (SIZE * calc->treshold
			/ calc->tmp);
	calc->line_top = (data->height / 2) - (SIZE * calc->treshold / calc->tmp);
	if (calc->line_top < 0)
		calc->line_top = 0;
	if (calc->line_bottom >= data->height)
		calc->line_bottom = data->height;
	y = calc->line_top;
	draw_wall(data, calc, block_width, y);
	draw_floor_ceiling(data, calc);
	temp_if_true = calc->tmp;
}

void	dda_vertical(t_data *data, t_calc_view *calc, bool if_true)
{
	int	x_dir;
	int	block_width;

	x_dir = 0;
	block_width = ft_get_block_width(calc);
	while (x_dir < QUALITY)
	{
		draw_vertical(data, calc, if_true, block_width);
		x_dir++;
		if (x_dir < QUALITY)
			calc->j++;
	}
}
