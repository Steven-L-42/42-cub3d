/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/11 21:21:19 by jsanger          ###   ########.fr       */
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

void	ft_free_structs(t_data *data)
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
	free(data->game->no);
	free(data->game->so);
	free(data->game->ea);
	free(data->game->we);
	free(data->game->f);
	free(data->game->c);
	mlx_delete_texture(data->img->txt_door_closed);
	mlx_delete_texture(data->img->txt_no);
	mlx_delete_texture(data->img->txt_so);
	mlx_delete_texture(data->img->txt_ea);
	mlx_delete_texture(data->img->txt_we);
	if (data->game->is_random_map)
		ft_free2d_char(data->game->rnd_map);
	ft_free2d_char(data->game->tmp_map);
	ft_free2d_char(data->game->map);
	ft_free2d_char(data->game->map_copy);
	ft_free2d_int(data->minimap->map);
	mlx_terminate(data->mlx);
	ft_free_structs(data);
}
