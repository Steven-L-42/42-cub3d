/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:40:45 by slippert          #+#    #+#             */
/*   Updated: 2024/01/12 10:50:08 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_init_vars(t_data *data)
{
	data->game->tmp_map = NULL;
	data->game->rnd_map = NULL;
	data->game->map = NULL;
	data->game->map_dda = NULL;
	data->minimap->map = NULL;
	data->is_started = false;
	data->is_torching = false;
	data->is_surrounded = false;
	data->game->width = 0;
}
