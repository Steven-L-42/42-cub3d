/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2023/12/27 20:35:19 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_helper(t_data *data, char *input)
{
	data->map = malloc(sizeof(t_map));
	data->minimap = malloc(sizeof(t_minimap));
	data->player = malloc(sizeof(t_player));
	get_map(data->map, input);
	if (data->map->width * SIZE < 1920)
		data->width = data->map->width * SIZE;
	else
		data->width = 1920;
	if (data->map->height * SIZE < 1080)
		data->height = data->map->height * SIZE;
	else
		data->height = 1080;
}

static void	init_img_info(t_data *data, mlx_texture_t *text)
{
	data->col_wood = get_color(text);
	data->wood_size[0] = text->width;
	data->wood_size[1] = text->height;
}

static int	init_img(t_data *data)
{
	mlx_texture_t	*text;

	text = mlx_load_png("textures/cross.png");
	data->img_game_cursor = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/brick_small.png");
	data->img_mm_wall = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);

	text = mlx_load_png("textures/brick_portal_small.png");
	data->img_mm_portal = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);

	text = mlx_load_png("textures/brick_door_closed_small.png");
	data->img_mm_door_closed = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);

	text = mlx_load_png("textures/brick_door_open_small.png");
	data->img_mm_door_open = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);

	text = mlx_load_png("textures/brick_shadow_small.png");
	data->img_mm_wall_shadow = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/player.png");
	data->img_player = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/brick.png");
	data->img_game_wall = mlx_texture_to_image(data->mlx, text);
	init_img_info(data, text);
	mlx_delete_texture(text);
	return (0);
}

static void	init_minimap(t_data *data)
{
	data->minimap->width = data->map->width;
	data->minimap->height = -1;
	data->minimap->map = ft_calloc(data->map->height + 1, sizeof(int *));
	while (++data->minimap->height < data->map->height)
		data->minimap->map[data->minimap->height] = ft_calloc(data->map->height + 1, sizeof(int));
}

int	init(t_data *data, char *input)
{
	init_helper(data, input);
	if (!(data->mlx = mlx_init(data->width, data->height, "cub3D", false)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	if (!(data->image = mlx_new_image(data->mlx, data->map->width * SIZE,
				data->map->height * SIZE)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	if (!(data->img_minimap = mlx_new_image(data->mlx, data->map->width * 16,
				data->map->height * 16)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	if (!(data->img_player_ray = mlx_new_image(data->mlx, data->map->width * 16,
				data->map->height * 16)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	init_img(data);
	init_minimap(data);
	init_coords(data, 0, 0);
	init_player(data);
	draw_minimap(data);
	return (0);
}
