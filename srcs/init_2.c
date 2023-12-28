/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2023/12/28 16:43:44 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_coords(t_data *data, int pixel_x, int pixel_y)
{
	int	i;
	int	j;

	i = 0;
	while (data->game->map[i])
	{
		j = 0;
		while (data->game->map[i][j])
		{
			if (data->game->map[i][j] == 'N' || data->game->map[i][j] == 'E'
				|| data->game->map[i][j] == 'S' || data->game->map[i][j] == 'W')
			{
				data->player->start_direction = data->game->map[i][j];
				data->game->map[i][j] = 'P';
				data->player->x = pixel_x;
				data->player->y = pixel_y;
				return ;
			}
			pixel_x += 1;
			j++;
		}
		pixel_x = 0;
		pixel_y += 1;
		i++;
	}
}

void	init_player(t_data *data)
{
	if (data->player->start_direction == 'N')
		data->player->angle = 270;
	if (data->player->start_direction == 'E')
		data->player->angle = 0;
	if (data->player->start_direction == 'S')
		data->player->angle = 90;
	if (data->player->start_direction == 'W')
		data->player->angle = 180;
	data->player->view_angle = 80;
	data->player->prev_mouseX = 0;
}
