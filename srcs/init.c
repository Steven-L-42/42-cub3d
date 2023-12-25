/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2023/12/25 13:23:25 by slippert         ###   ########.fr       */
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
				data->player->x = pixel_x;
				data->player->y = pixel_y;
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


void hex_to_rgb(char *hex, int *r, int *g, int *b)
{
	long int hexValue = strtol(hex, NULL, 16);
	*r = (hexValue >> 16) & 0xFF;
	*g = (hexValue >> 8) & 0xFF;
	*b = hexValue & 0xFF;
}

void	color_parser(t_data *data)
{
	int	y;
	int	x;
	int r, g, b;
	y = 0;
	int	fd = open("textures/colors.col", O_RDONLY);

	char **buffer = ft_calloc(100, sizeof(char *));
	int buf = 0;

	char *line = get_next_line(fd);
	int keys = 0;
	while (line)
	{
		int i = 0;
		buf = 0;
		data->key[keys] = line[i++];
		i++;
		buffer[keys] = ft_calloc(100, 1);
		i++;
		while (line[i] && line[i] != 'F' && line[i] != '\n')
			buffer[keys][buf++] = line[i++];
		buffer[keys][buf++] = '\0';
		keys++;
		free(line);
		if (keys >= 31)
			break;
		line = get_next_line(fd);
	}
	for	(int i = 0; i < 31; i++)
	{
		hex_to_rgb(buffer[i], &r, &g, &b);
		data->color[i] = ft_pixel(r, g, b, 255);
		ft_printf("%c %s %d | RGB %d %d %d\n", data->key[i], buffer[i], data->color[i], r, g, b);
	}
	close(fd);
	fd = open("textures/woodn.xpm42", O_RDONLY);
	line = get_next_line(fd);
	while(y < 1024)
	{
		data->wood[y] = line;
		//ft_printf("%s\n", data->wood[y]);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
}

int	init(t_data *data, t_map *map, t_player *player, char *input)
{
	mlx_texture_t	*text;
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
	text = mlx_load_png("textures/cross.png");
	mlx_win_cursor_t *cursor = mlx_create_cursor(text);
	mlx_delete_texture(text);
	mlx_set_cursor(data->mlx, cursor);
	text = mlx_load_png("textures/wall.png");
	data->img_game_wall = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);

	text = mlx_load_png("textures/player.png");
	data->img_player = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);

	data->text_wood = mlx_load_png("textures/wood.png");



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
