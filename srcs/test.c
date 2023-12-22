/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/22 14:22:45 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	reset(t_data *data)
{
	ft_memset(data->image->pixels, 0, data->image->width * data->image->height
		* sizeof(int32_t));
}

void	calc_view(t_data *data)
{
	float		temp1;
	float		temp2;
	int			j;
	int			angle;
	float		height;
	float		tmp;
	float		linehight;
	float		linehight1;
	uint32_t	color;

	j = 0;
	temp1 = data->player->view_angle / 2;
	temp2 = -temp1;
	angle = temp1;
	static int testads = 0;
	color = ft_pixel(0, 255, 255, 255);
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, data->map->width * SIZE, data->map->height * SIZE);
	for (float k = temp2; k < temp1; k++)
	{
		height = ray_distance(data, k);
		for (float i = (data->image->width / data->player->view_angle)
			* j; i < (data->image->width / data->player->view_angle) * (j
				+ 1); ++i)
		{
			tmp = height * cos((angle)*PI / 180);
			linehight = (data->image->height / 2) + (SIZE * 3 / tmp);
			linehight1 = (data->image->height / 2) - (SIZE * 3 / tmp);
			if (linehight1 < 0)
				linehight1 = 0;
			if (linehight >= data->image->height)
				linehight = data->image->height;
			for (int32_t y = data->image->height / 2; y < linehight; y++)
			{
				mlx_put_pixel(data->image, i, y, color);
			}
			for (int32_t y = data->image->height / 2; y > linehight1; y--)
			{
				mlx_put_pixel(data->image, i, y, color);
			}
		}
		angle--;
		j++;
	}

	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

int	check_for_wall_ahead(t_data *data, float distance, float radianAngle)
{
	float	p_x_cos;
	float	p_y_sin;
	int		cellX;
	int		cellY;

	if (distance > 0)
		distance = 1;
	else
		distance = -1;
	p_x_cos = cos(radianAngle);
	p_y_sin = sin(radianAngle);
	cellX = (int)data->player->x + distance * p_x_cos;
	cellY = (int)data->player->y + distance * p_y_sin;
	if (cellY <= 0 || cellY >= data->map->height - 1 || cellX <= 0
		|| cellX >= data->map->width - 1)
		return (1);
	if (data->map->map[cellY][cellX] == '1')
		return (1);
	return (0);
}

void	move_player(t_data *data, float speed, int forward)
{
	float	radianAngle;
	float	p_x_cos;
	float	p_y_sin;

	if (forward == 1)
		radianAngle = data->player->angle * PI / 180.0;
	else
		radianAngle = (data->player->angle + 90.0) * PI / 180.0;
	if (check_for_wall_ahead(data, speed, radianAngle))
		return ;
	p_x_cos = speed * cos(radianAngle);
	p_y_sin = speed * sin(radianAngle);
	data->player->x += p_x_cos;
	data->player->y += p_y_sin;
	data->img_player->instances[0].x = data->player->x * 16;
	data->img_player->instances[0].y = data->player->y * 16;
}

void	update_player_angle(double xpos, double ypos, void *param)
{
	t_data	*data;
	float	deltaX;
	float	deltaY;
	float	newAngle;
	float	sensitivity;
	int		mouseX;
	int		mouseY;

	data = param;
	mlx_get_mouse_pos(data->mlx, &mouseX, &mouseY);
	deltaX = mouseX - data->player->x;
	deltaY = mouseY - data->player->y;
	newAngle = -atan2(deltaY, deltaX) * 180.0 / M_PI;
	sensitivity = 3.0;
	data->player->angle = sensitivity * newAngle;
	reset(data);
	calc_view(data);
}
#include <limits.h>
void	draw_player_rays(t_data *data, int num_rays)
{
	uint32_t	color;
	float		angle_offset;
	float		end_x;
	float		end_y;
	int			x_coord;
	int			y_coord;

	ft_memset(data->img_player_ray->pixels, 0, data->img_player_ray->width
		* data->img_player_ray->height * sizeof(int32_t));
	color = ft_pixel(0, 255, 128, 255);
	for (int i = -num_rays / 2; i <= num_rays / 2; i++)
	{
		angle_offset = i;
		end_x = data->player->x * 16 + 8  * cos((data->player->angle
					+ angle_offset) * PI / 180);
		end_y = data->player->y * 16 + 8  * sin((data->player->angle
					+ angle_offset) * PI / 180);
		for (int j = 0; j < INT_MAX / 2; j++)
		{
			x_coord = data->player->x * 16 + 8 + j * cos((data->player->angle
						+ angle_offset) * PI / 180);
			y_coord = data->player->y * 16 + 8 + j * sin((data->player->angle
						+ angle_offset) * PI / 180);

			if (x_coord >= 0 && y_coord >= 0
				&& x_coord < data->img_player_ray->width
				&& y_coord < data->img_player_ray->height)
			{
				if (data->map->map[y_coord / 16][x_coord / 16] == '1')
					break ;
				mlx_put_pixel(data->img_player_ray, x_coord, y_coord, color);
			}
		}
	}
	mlx_image_to_window(data->mlx, data->img_player_ray, 0, 0);
}

void	ft_running(void *param)
{
	t_data	*data;

	data = param;
	reset(data);
	calc_view(data);
	draw_player_rays(data, 90);
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(data->mlx, data->image);
		ft_exit(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		move_player(data, 0.05, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		move_player(data, -0.05, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		move_player(data, -0.05, 0);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		move_player(data, 0.05, 0);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player->angle += 5;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player->angle -= 5;
	}
}

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

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->game_wall, x * 16, y * 16);
			else if (data->map->map[y][x] == 'P')
				mlx_image_to_window(data->mlx, data->img_player, data->player->x
					* 16, data->player->y * 16);
			x++;
		}
		// ft_printf("%s\n", data->map->map[y]);
		y++;
	}
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

int	main(int argc, char **argv)
{
	t_map		*map;
	t_player	*player;
	t_data		*data;

	data = malloc(sizeof(t_data));
	map = malloc(sizeof(t_map));
	player = malloc(sizeof(t_player));
	if (init(data, map, player, argv[1]))
		return (1);
	//	mlx_cursor_hook(data->mlx, update_player_angle, data);
	mlx_loop_hook(data->mlx, ft_running, data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	ft_exit(data);
}
