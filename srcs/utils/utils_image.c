/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/05 13:15:54 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_open_image(t_data *data, mlx_image_t **img_direction, char *img_path)
{
	mlx_texture_t	*text;

	text = mlx_load_png(img_path);
	if (!text)
		return (1);
	*img_direction = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	return (0);
}

int	ft_open_image_keep_text(t_data *data, mlx_image_t **img_direction,
		mlx_texture_t **text, char *img_path)
{
	*text = mlx_load_png(img_path);
	*img_direction = mlx_texture_to_image(data->mlx, *text);
	return (0);
}
