/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/09 19:07:31 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free2d_until(char **str, int max_len)
{
	int	i;

	i = 0;
	while (str[i] != NULL && i < max_len)
		free(str[i++]);
	free(str);
}

void	ft_free2d_char(char **str)
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

void	free_structs(t_data *data)
{
	if (data->player != NULL)
		free(data->player);
	if (data->minimap != NULL)
		free(data->minimap);
	if (data->game != NULL)
		free(data->game);
	if (data->img != NULL)
		free(data->img);
	if (data != NULL)
		free(data);
}

void	ft_exit(t_data *data)
{
	free(data->game->NO);
	free(data->game->SO);
	free(data->game->EA);
	free(data->game->WE);
	free(data->game->F);
	free(data->game->C);
	mlx_delete_texture(data->img->txt_door_closed);
	mlx_delete_texture(data->img->txt_NO);
	mlx_delete_texture(data->img->txt_SO);
	mlx_delete_texture(data->img->txt_EA);
	mlx_delete_texture(data->img->txt_WE);
	if (data->game->is_random_map)
		ft_free2d_char(data->game->rnd_map);
	ft_free2d_char(data->game->tmp_map);
	ft_free2d_char(data->game->map);
	ft_free2d_char(data->game->map_copy);
	ft_free2d_int(data->minimap->map);
	mlx_terminate(data->mlx);
	free_structs(data);
}
