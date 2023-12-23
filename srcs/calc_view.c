/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:25 by slippert          #+#    #+#             */
/*   Updated: 2023/12/23 19:51:34 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Funktion: calc_preset
// Zweck: Initialisiert die notwendigen Werte für die Berechnung der Sichtlinien.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - calc: Zeiger auf die Struktur,
//		die Informationen für die Berechnungen enthält.
//
// Die Funktion setzt verschiedene Werte wie Winkel, Farben und Zählvariablen
// für die Berechnungen der Sichtlinien. Zudem wird der bestehende Bildspeicher
// gelöscht und ein neuer Bildspeicher für die Sichtlinien erstellt.
void	calc_preset(t_data *data, t_calc_view *calc)
{
	calc->j = 0;
	calc->temp1 = data->player->view_angle / 2;
	calc->temp2 = -calc->temp1;
	calc->angle = calc->temp1;
	calc->color_front = ft_pixel(0, 255, 255, 255);
	calc->color_side = ft_pixel(0, 100, 255, 255);
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, data->map->width * SIZE,
			data->map->height * SIZE);
	calc->k = calc->temp2;
}

int	get_colour_from_pixel(u_int8_t *pixel)
{
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static int	calculate_texture_height_pixels(mlx_texture_t *texture, t_data *ray,
	int draw_height)
{
	int		height;
	float	height_divided;

	if (ray->wall_height > 64)
		draw_height += (ray->wall_height - 64) / 2;
	height_divided = texture->height / ray->wall_height;
	height = floor((height_divided * draw_height)) * texture->width;
	return (height);
}

static int	get_texture_pixel_color(mlx_texture_t *texture, t_data *ray,
	float current_height, int width_pixels)
{
	u_int8_t	*pixel;
	int			pixel_texture_location;

	pixel_texture_location = calculate_texture_height_pixels(texture, ray,
			current_height);
	pixel_texture_location += width_pixels;
	pixel_texture_location *= texture->bytes_per_pixel;
	pixel = &texture->pixels[pixel_texture_location];
	return (get_colour_from_pixel(pixel));
}

// Funktion: calc_helper
// Zweck: Hilfsfunktion für die Berechnung und Darstellung der Sichtlinien.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - calc: Zeiger auf die Struktur,
// die Informationen für die Berechnungen enthält.
//
// Die Funktion führt die eigentlichen Berechnungen für die Sichtlinien durch. Sie
// berechnet die Höhe der Linien, die auf dem Bildschirm dargestellt werden,
// basierend auf der Entfernung und dem Winkel.
// Anschließend werden die entsprechenden Pixel im Bildspeicher markiert.
void	calc_helper(t_data *data, t_calc_view *calc)
{
	int	tmp;
	int	y;
	int		color;

	tmp = (data->image->width / data->player->view_angle) * (calc->j + 1);
	while (calc->i < tmp)
	{
		calc->tmp = calc->distance * cos((calc->angle) * PI / 180);
		calc->line_bottom = (data->image->height / 2) + (SIZE * 6 / calc->tmp);
		calc->line_top = (data->image->height / 2) - (SIZE * 6 / calc->tmp);
		if (calc->line_top < 0)
			calc->line_top = 0;
		if (calc->line_bottom >= data->image->height)
			calc->line_bottom = data->image->height;
		y = (data->image->height / 2) + 1;
		color = get_texture_pixel_color(data->text_wood, data, y, calc->i);
		while (--y > calc->line_top)
			mlx_put_pixel(data->image, calc->i, y, color);
		y = (data->image->height / 2) - 1;
		while (++y < calc->line_bottom)
			mlx_put_pixel(data->image, calc->i, y, color);
		calc->i++;
	}
}

// Funktion: calc_view
// Zweck: Berechnet und zeichnet die Sichtlinien im Spiel.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//
// Die Funktion initialisiert die notwendigen Werte, iteriert über die
// Sichtlinien und ruft die Hilfsfunktion calc_helper für jede Sichtlinie auf.
// Das Ergebnis wird im Fenster angezeigt.
void	calc_view(t_data *data)
{
	t_calc_view	calc;

	calc_preset(data, &calc);
	while (calc.k < calc.temp1)
	{
		calc.distance = ray_distance(data, calc.k);
		calc.i = (data->image->width / data->player->view_angle) * calc.j;
		calc_helper(data, &calc);
		calc.angle--;
		calc.j++;
		calc.k++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	data->image->instances[0].z = 0;
}

// void	calc_view(t_data *data)
// {
// 	float		temp1;
// 	float		temp2;
// 	int			j;
// 	int			angle;
// 	float		distance;
// 	float		tmp;
// 	float		linehight;
// 	float		linehight1;
// 	uint32_t	color_front;
// 	uint32_t	color_side;
// 	int			is_side;
// 	float		k;
// 	float		i;
// 	j = 0;
// 	temp1 = data->player->view_angle / 2;
// 	temp2 = -temp1;
// 	angle = temp1;
// 	color_front = ft_pixel(0, 255, 255, 255);
// 	color_side = ft_pixel(0, 100, 255, 255);
// 	mlx_delete_image(data->mlx, data->image);
// 	data->image = mlx_new_image(data->mlx, data->map->width * SIZE,
// 			data->map->height * SIZE);
// 	k = temp2;
// 	while (k < temp1)
// 	{
// 		distance = ray_distance(data, k);
// 		i = (data->image->width / data->player->view_angle) * j;
// 		while (i < (data->image->width / data->player->view_angle) * (j + 1))
// 		{
// 			tmp = distance * cos((angle)*PI / 180);
// 			linehight = (data->image->height / 2) + (SIZE * 3 / tmp);
// 			linehight1 = (data->image->height / 2) - (SIZE * 3 / tmp);
// 			if (linehight1 < 0)
// 				linehight1 = 0;
// 			if (linehight >= data->image->height)
// 				linehight = data->image->height;
// 			for (int32_t y = data->image->height / 2; y < linehight; y++)
// 			{

// 					mlx_put_pixel(data->image, i, y, color_side);
// 			}
// 			for (int32_t y = data->image->height / 2; y > linehight1; y--)
// 			{

// 					mlx_put_pixel(data->image, i, y, color_side);
// 			}
// 			i++;
// 		}
// 		angle--;
// 		j++;
// 		k++;
// 	}
// 	mlx_image_to_window(data->mlx, data->image, 0, 0);
// }
