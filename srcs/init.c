/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2023/12/22 15:02:15 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_player_coords(t_data *data)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = 0;
	pixel_y = 0;
	for (int i = 0; data->map->map[i] != NULL; i++)
	{
		for (int j = 0; data->map->map[i][j] != '\0'; j++)
		{
			if (data->map->map[i][j] == 'P')
			{
				data->player->x = pixel_x + 0.5;
				data->player->y = pixel_y + 0.5;
				return ;
			}
			pixel_x += 1;
		}
		pixel_x = 0;
		pixel_y += 1;
	}
}

void	struct_declaration(t_data *data)
{
	data->player->angle = 90;
	data->player->x = 0;
	data->player->y = 0;
	data->player->view_angle = 80;
}

int	init(t_data *data, t_map *map, t_player *player, char *input)
{
	mlx_texture_t	*text_wall;
	mlx_texture_t	*text_player;

	get_map(map, input);
	map->width -= 1;
	if (!(data->mlx = mlx_init(map->width * SIZE, map->height * SIZE, "MLX42",
				true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	if (!(data->image = mlx_new_image(data->mlx, map->width * SIZE, map->height
				* SIZE)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		exit(1);
	}
	if (!(data->img_player_ray = mlx_new_image(data->mlx, map->width * 16,
				map->height * 16)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		exit(1);
	}
	text_wall = mlx_load_png("textures/wall.png");
	text_player = mlx_load_png("textures/player.png");
	data->game_wall = mlx_texture_to_image(data->mlx, text_wall);
	data->img_player = mlx_texture_to_image(data->mlx, text_player);
	data->player = player;
	data->map = map;
	struct_declaration(data);
	get_player_coords(data);
	reset(data);
	calc_view(data);
	draw_minimap(data);
	return (0);
}