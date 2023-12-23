/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2023/12/23 21:46:15 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_player_coords(t_data *data)
{
	int	pixel_x;
	int	pixel_y;
	int	i;
	int	j;

	pixel_x = 0;
	pixel_y = 0;
	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j] != '\0')
		{
			if (data->map->map[i][j] == 'P')
			{
				data->player->x = pixel_x + 0.5;
				data->player->y = pixel_y + 0.5;
				return ;
			}
			pixel_x += 1;
			j++;
		}
		pixel_x = 0;
		pixel_y += 1;
		i++;
	}
}

void	struct_declaration(t_data *data)
{
	data->player->angle = 90;
	data->player->x = 0;
	data->player->y = 0;
	data->player->view_angle = 80;
}

#include <stdint.h>

typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
} RGBA;


RGBA hexToRGBA(char *hexString)
{
	uint32_t hexValue = atoi(hexString + 1);
	RGBA result;
	// Extrahiere die Farbkomponenten
	result.red = (hexValue >> 24) & 0xFF;
	result.green = (hexValue >> 16) & 0xFF;
	result.blue = (hexValue >> 8) & 0xFF;
	result.alpha = hexValue & 0xFF;

	return result;
}

void	color_parser(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	int	fd = open("textures/colors.col", O_RDONLY);

	char **buffer = ft_calloc(10, sizeof(char *));
	int buf = 0;

	char *line = get_next_line(fd);
	int keys = 0;
	while (line)
	{
		int i = 0;
		buf = 0;
		data->key[keys] = line[i++];
		i++;
		buffer[keys] = ft_calloc(10, 1);
		while (line[i] && line[i] != '\n')
			buffer[keys][buf++] = line[i++];
		buffer[keys][buf++] = '\0';
		keys++;
		free(line);
		if (keys >= 9)
			break;
		line = get_next_line(fd);
	}
	//ft_printf("%s", buffer);
	for	(int i = 0; i < 9; i++)
	{
		buffer[i][7] = '\0';
		RGBA rgba = hexToRGBA(buffer[i]);
		data->color[i] = ft_pixel(rgba.red, rgba.green, rgba.blue, 255);
		ft_printf("%c %s %d\n", data->key[i], buffer[i], data->color[i]);
		// ft_printf("RGBA %d %d %d\n", rgba.red, rgba.green, rgba.blue);

	}
	close(fd);
	fd = open("textures/wood.xpm42", O_RDONLY);
	line = get_next_line(fd);
	while(y < 64)
	{
		data->wood[y] = line;
		//ft_printf("%s\n", data->wood[y]);
		free(line);
		line = get_next_line(fd);
		y++;
	}

}

int	init(t_data *data, t_map *map, t_player *player, char *input)
{
	get_map(map, input);
	map->width -= 1;
	if (!(data->mlx = mlx_init(map->width * SIZE, map->height * SIZE, "cub3D",
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
	if (!(data->img_minimap = mlx_new_image(data->mlx, map->width * 16,
				map->height * 16)))
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
	data->text_wall = mlx_load_png("textures/wall.png");
	data->text_player = mlx_load_png("textures/player.png");
	data->text_wood = mlx_load_png("textures/wood.png");
	data->img_game_wall = mlx_texture_to_image(data->mlx, data->text_wall);
	data->img_player = mlx_texture_to_image(data->mlx, data->text_player);
	data->player = player;
	data->map = map;
	struct_declaration(data);
	color_parser(data);
	data->player->prev_mouseX = 0;
	get_player_coords(data);
	reset(data);
	calc_view(data);
	draw_minimap(data);
	return (0);
}
