/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_pistol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/09 15:34:30 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_pistol_anim(void *param)
{
	t_data	*data;
	int		i;

	data = (void *)param;
	if (data->is_shooting == true || data->img->pistol_frame > 0)
	{
		data->is_shooting = false;
		i = 0;
		while (i < 5)
		{
			if (data->img->pistol_frame == i)
				data->img->img_pistol[i++]->enabled = true;
			else
				data->img->img_pistol[i++]->enabled = false;
		}
		data->img->pistol_frame++;
		data->img->pistol_frame = data->img->pistol_frame % 5;
	}
}
