/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/22 14:48:55 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	reset(t_data *data)
{
	ft_memset(data->image->pixels, 0, data->image->width * data->image->height
		* sizeof(int32_t));
}

void ft_free2d(char **str)
{
	for (int i = 0; str[i] != NULL; i++)
	{
		free(str[i]);
	}
	free(str);
}

void	ft_exit(t_data *data)
{
	// ft_free2d(data->map->map);
	mlx_terminate(data->mlx);
	free(data->map);
	free(data);
	exit(0);
}
