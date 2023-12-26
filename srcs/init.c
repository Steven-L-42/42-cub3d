/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:01:37 by slippert          #+#    #+#             */
/*   Updated: 2023/12/26 12:28:45 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_coords(t_data *data, int pixel_x, int pixel_y)
{
	int	i;
	int	j;

	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == 'N' || data->map->map[i][j] == 'E'
				|| data->map->map[i][j] == 'S' || data->map->map[i][j] == 'W')
			{
				data->player->start_direction = data->map->map[i][j];
				data->map->map[i][j] = 'P';
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

void	init_player(t_data *data)
{
	if (data->player->start_direction == 'N')
		data->player->angle = 270;
	if (data->player->start_direction == 'E')
		data->player->angle = 0;
	if (data->player->start_direction == 'S')
		data->player->angle = 90;
	if (data->player->start_direction == 'W')
		data->player->angle = 180;
	data->player->view_angle = 80;
	data->player->prev_mouseX = 0;
}

// ABFALL
void	init_colors(t_data *data)
{
	int		y;
	int		x;
	int		fd;
	char	**buffer;
	int		buf;
	char	*line;
	int		keys;
	int		i;

	int r, g, b;
	y = 0;
	fd = open("textures/colors.col", O_RDONLY);
	buffer = ft_calloc(100, sizeof(char *));
	buf = 0;
	line = get_next_line(fd);
	keys = 0;
	while (line)
	{
		i = 0;
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
			break ;
		line = get_next_line(fd);
	}
	for (int i = 0; i < 31; i++)
	{
		hex_to_rgb(buffer[i], &r, &g, &b);
		data->color[i] = ft_pixel(r, g, b, 255);
		ft_printf("%c %s %d | RGB %d %d %d\n", data->key[i], buffer[i],
			data->color[i], r, g, b);
	}
	close(fd);
	fd = open("textures/woodn.xpm42", O_RDONLY);
	line = get_next_line(fd);
	while (y < 1024)
	{
		data->wood[y] = line;
		// ft_printf("%s\n", data->wood[y]);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
}

static void	init_helper(t_data *data, char *input)
{
	data->map = malloc(sizeof(t_map));
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

uint32_t	*get_color(mlx_texture_t *texture)
{
	int				i;
	unsigned int	pos;
	uint8_t			rgb[4];
	uint32_t		*colors;

	i = 0;
	colors = malloc(sizeof(uint32_t) * (texture->width + 1) * (texture->height + 1));
	if (colors == NULL)
		return (NULL);
	pos = 0;
	while (pos < texture->width * texture->height * texture->bytes_per_pixel)
	{
		rgb[0] = texture->pixels[pos];
		rgb[1] = texture->pixels[pos + 1];
		rgb[2] = texture->pixels[pos + 2];
		rgb[3] = texture->pixels[pos + 3];
		colors[i] = (rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3];
		pos += texture->bytes_per_pixel;
		i++;
	}
	return (colors);
}

void	init_img_info(t_data *data, mlx_texture_t *text)
{
	data->col_wood = get_color(text);
	data->wood_size[0] = text->width;
	data->wood_size[1] = text->height;
}

int	init_img(t_data *data)
{
	mlx_texture_t	*text;

	text = mlx_load_png("textures/cross.png");
	data->img_cursor = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/wall.png");
	data->img_game_wall = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/player.png");
	data->img_player = mlx_texture_to_image(data->mlx, text);
	mlx_delete_texture(text);
	text = mlx_load_png("textures/wood.png");
	data->img_wood = mlx_texture_to_image(data->mlx, text);
	init_img_info(data, text);
	mlx_delete_texture(text);
	return (0);
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
	// init_colors(data);
	init_coords(data, 0, 0);
	init_player(data);
	draw_minimap(data);
	return (0);
}
