/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_view2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 21:22:27 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/05 13:02:24 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_line(t_data *data, t_calc_view *calc, bool if_true,
		int block_width)
{
	float			y;
	float			t;
	float			block_height;
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
	while (y < calc->line_bottom)
	{
		block_height = calc_for_x(calc->line_bottom - calc->line_top, y
				- calc->line_top, BLOCK_PIXEL_SIZE);
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
		mlx_put_pixel(data->img->img_game, calc->j, y, calc->color_wall);
				y++;
	}
	t = -1;
	while (++t < calc->line_top)
		mlx_put_pixel(data->img->img_game, calc->j, t,
			data->game->color_ceiling);
	t = calc->line_bottom - 1;
	while (++t < data->height)
		mlx_put_pixel(data->img->img_game, calc->x, t, data->game->color_floor);
	temp_if_true = calc->tmp;
}

void	draw_texture(t_data *data, t_calc_view *calc, bool if_true)
{
	int x_dir = 0;
	float temp;
	int i = 0;

	while (calc->width_array[i] < calc->j)
	{
		i++;
		if (calc->width_array[i] != (float)0 && calc->width_array[i] < FLT_MAX)
		{
			temp = (int)calc_for_x(calc->width_array[i] - calc->width_array[i
					- 1], calc->j - calc->width_array[i - 1], BLOCK_PIXEL_SIZE);
		}
	}
	while (x_dir < QUALITY)
	{
		draw_line(data, calc, if_true, temp);
		x_dir++;
		if (x_dir < QUALITY)
			calc->j++;
	}
}