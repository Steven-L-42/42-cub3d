/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/27 15:07:27 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	free(data->player);
	free(data->map);
	free(data->col_wood);
	free(data);
	mlx_terminate(data->mlx);
	exit(0);
}
