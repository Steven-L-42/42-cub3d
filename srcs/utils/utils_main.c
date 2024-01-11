/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:08:51 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/11 14:04:19 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_crosshair(t_data *data, uint32_t color)
{
	t_crosshair	cross;

	ft_memset(data->img->img_crosshair->pixels, 0,
		data->img->img_crosshair->width * data->img->img_crosshair->height
		* sizeof(int32_t));
	cross.middle_x = data->img->img_crosshair->width / 2;
	cross.tmp_middle_x = cross.middle_x;
	cross.middle_y = data->img->img_crosshair->height / 2;
	cross.color = color;
	cross.radius = 18;
	draw_hori(data, cross);
	draw_verti(data, cross);
	draw_leftdiagonal(data, cross);
	draw_rightdiagonal(data, cross);
	draw_circle(data, cross);
}

static void	ft_img_to_window_helper(t_data *data)
{
	mlx_image_to_window(data->mlx, data->img->img_mm_overlay, 0, 0);
	mlx_image_to_window(data->mlx, data->img->img_game, 0, 0);
	mlx_image_to_window(data->mlx, data->img->img_movement_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->img->img_crosshair, data->width / 2
		- data->img->img_crosshair->width / 2, data->height / 2
		- data->img->img_crosshair->height / 2);
	draw_crosshair(data, data->cross_colors[0]);
	data->img->pistol_frame = 0;
	data->img->img_game->instances[0].z = 0;
}

void	ft_img_to_window(t_data *data)
{
	int	width;
	int	height;
	int	i;

	i = -1;
	draw_minimap(data);
	width = data->width / 2 - data->img->img_pistol[0]->width / 2;
	height = data->height - data->img->img_pistol[0]->height;
	mlx_image_to_window(data->mlx, data->img->img_player_ray, 0, 0);
	while (++i < 5)
	{
		mlx_image_to_window(data->mlx, data->img->img_pistol[i], width, height);
		if (i < 4)
			data->img->img_pistol[i]->enabled = false;
	}
	i = -1;
	width = data->width / 2 + data->img->img_torch[0]->width / 2;
	height = data->height - data->img->img_torch[0]->height;
	while (++i < 6)
	{
		mlx_image_to_window(data->mlx, data->img->img_torch[i], width, height);
		data->img->img_torch[i]->enabled = false;
	}
	ft_img_to_window_helper(data);
}

void	ft_check_is_explored(t_data *data)
{
	uint32_t	max;
	int			start;
	uint32_t	count;
	int			color;

	color = ft_pixel(0, 0, 0, 0);
	max = data->img->img_mm_overlay->width * data->img->img_mm_overlay->height
		* sizeof(uint32_t);
	start = 0;
	count = 0;
	while (start < max)
	{
		if (data->img->img_mm_overlay->pixels[start] == color)
			count++;
		start++;
	}
	if (count >= 0.75 * max)
	{
		ft_memset(data->img->img_mm_overlay->pixels, 0,
			data->img->img_mm_overlay->width * data->img->img_mm_overlay->height
			* sizeof(uint32_t));
		data->game->is_explored = true;
	}
}

void	draw_map_explored(t_data *data, int r, int x, int y)
{
	int		x_middle;
	int		y_middle;
	int		radius;
	double	angle;
	int		color;

	x_middle = data->player->x * 16 + 6;
	y_middle = data->player->y * 16 + 6;
	radius = 50;
	angle = 0;
	color = ft_pixel(0, 0, 0, 0);
	while (angle <= 2 * M_PI)
	{
		r = 0;
		while (r <= radius)
		{
			x = x_middle + (int)(r * cos(angle));
			y = y_middle + (int)(r * sin(angle));
			if (x >= 0 && y >= 0 && x < data->img->img_mm_overlay->width
				&& y < data->img->img_mm_overlay->height)
				mlx_put_pixel(data->img->img_mm_overlay, x, y, color);
			++r;
		}
		angle += 0.01;
	}
}

void	ft_running(void *param)
{
	t_data	*data;

	data = param;
	reset_window(data);
	dda_horizontal(data);
	draw_player_rays(data, 80);
	if (!data->game->is_explored)
	{
		draw_map_explored(data, 0, 0, 0);
		ft_check_is_explored(data);
	}
}

int	ft_check_extension(char *argv)
{
	int			len;
	int			i;
	const char	*extension = ".cub";

	len = ft_strlen(argv) - 4;
	i = 0;
	while (extension[i])
	{
		if (!argv[len] || extension[i] != argv[len])
		{
			ft_error("Error: Map extension incorrect. Expected: (.cub)");
			return (1);
		}
		len++;
		i++;
	}
	return (0);
}
