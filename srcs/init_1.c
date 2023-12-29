/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2023/12/29 13:16:45 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	init_helper(t_data *data, char *input)
{
	data->game = malloc(sizeof(t_map));
	data->minimap = malloc(sizeof(t_minimap));
	data->player = malloc(sizeof(t_player));
	if (get_map(data->game, input))
		return (1);
	if (data->game->width * SIZE < 1920)
		data->width = data->game->width * SIZE;
	else
		data->width = 1920;
	if (data->game->height * SIZE < 1080)
		data->height = data->game->height * SIZE;
	else
		data->height = 1080;
	return (0);
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
	data->img->img_game_cursor = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/brick_small.png");
	data->img->img_mm_wall = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/brick_portal_small.png");
	data->img->img_mm_portal = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/brick_door_closed_small.png");
	data->img->img_mm_door_closed = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/brick_door_open_small.png");
	data->img->img_mm_door_open = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/brick_shadow_small.png");
	data->img->img_mm_wall_shadow = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/player.png");
	data->img->img_player = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/brick.png");
	data->img->img_game_wall = mlx_texture_to_image(data->mlx, text);
	init_img_info(data, text);
	mlx_delete_texture(text);
	return (0);
}

static void	init_minimap(t_data *data)
{
	data->minimap->width = data->game->width;
	data->minimap->height = -1;
	data->minimap->map = ft_calloc(data->game->height + 1, sizeof(int *));
	while (++data->minimap->height < data->game->height)
		data->minimap->map[data->minimap->height] = ft_calloc(data->game->height
				+ 1, sizeof(int));
}

int	init(t_data *data, char *input)
{
	data->img = malloc(sizeof(t_img));
	if (init_helper(data, input))
		return (1);
	if (!(data->mlx = mlx_init(data->width, data->height, "cub3D", false)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	if (!(data->img->img_game = mlx_new_image(data->mlx, data->game->width
				* SIZE, data->game->height * SIZE)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	if (!(data->img->img_player_ray = mlx_new_image(data->mlx, data->game->width
				* 16, data->game->height * 16)))
		return (puts(mlx_strerror(mlx_errno)), 1);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	init_img(data);
	init_minimap(data);
	init_coords(data, 0, 0);
	init_player(data);
	draw_minimap(data);
	return (0);
}
