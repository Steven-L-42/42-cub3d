/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/27 20:54:36 by slippert         ###   ########.fr       */
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

void	ft_free2d_int(int **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

int		ft_is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_data *data)
{
	ft_free2d(data->map->map);
	ft_free2d_int(data->minimap->doors);
	free(data->player);
	free(data->map);
	free(data->minimap);
	free(data->col_wood);
	free(data);
	mlx_terminate(data->mlx);
	exit(0);
}
