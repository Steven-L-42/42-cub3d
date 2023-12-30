/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/30 13:48:50 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_img_info(t_data *data, mlx_texture_t *text)
{
	data->col_texture = get_color(text);
	data->wood_size[0] = text->width;
	data->wood_size[1] = text->height;
}

int	ft_open_image(t_data *data, mlx_image_t **img_direction, char *img_path, int need_info)
{
	mlx_texture_t	*text;

	text = mlx_load_png(img_path);
	if (!text)
		return (1);
	*img_direction = mlx_texture_to_image(data->mlx, text);
	if (need_info)
		init_img_info(data, text);
	mlx_delete_texture(text);
	return (0);
}
