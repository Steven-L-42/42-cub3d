/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/26 14:28:09 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_colour_from_pixel(u_int8_t *pixel)
{
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	hex_to_rgb(char *hex, int *r, int *g, int *b)
{
	long int	hexValue;

	hexValue = strtol(hex, NULL, 16);
	*r = (hexValue >> 16) & 0xFF;
	*g = (hexValue >> 8) & 0xFF;
	*b = hexValue & 0xFF;
}

void	reset_window(t_data *data)
{
	ft_memset(data->image->pixels, 0, data->image->width * data->image->height
		* sizeof(int32_t));
}

void	ft_free2d(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}



void	ft_exit(t_data *data)
{
	ft_free2d(data->map->map);
	mlx_terminate(data->mlx);
	free(data->player);
	free(data->map);
	free(data->col_wood);
	free(data);
	exit(0);
}
