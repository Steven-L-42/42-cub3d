/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/29 11:43:19 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	return (1);
}

void	reset_window(t_data *data)
{
	ft_memset(data->img->img_game->pixels, 0, data->img->img_game->width
		* data->img->img_game->height * sizeof(int32_t));
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

int	ft_is_in_set(char c, char *set)
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
	ft_free2d(data->game->map);
	free(data->game);
	ft_free2d_int(data->minimap->map);
	free(data->minimap);
	free(data->player);
	free(data->col_wood);
	free(data->img);
	mlx_terminate(data->mlx);
	free(data);
	exit(0);
}
