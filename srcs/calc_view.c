/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:25 by slippert          #+#    #+#             */
/*   Updated: 2024/01/03 17:28:43 by slippert         ###   ########.fr       */
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
	calc->max_lines = -(data->player->view_angle / 2);
	calc->temp2 = -calc->max_lines;
	calc->angle = -calc->max_lines;
	calc->color_wall = ft_pixel(56, 76, 200, 255);
	calc->color_door = ft_pixel(125, 76, 56, 255);
	calc->color_portal = ft_pixel(56, 125, 125, 255);
	calc->line = calc->max_lines * -1;
	calc->treshold = (float)6.2f * (data->width / 1920.0);
	calc->direction = '\0';
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
	double	line_width;
	int		y;
	int		size_x;
	int		size_y;
	int		t;

	line_width = (data->width / data->player->view_angle) * (calc->j + 1);
	while (calc->x < line_width)
	{
		calc->tmp = calc->distance * cos((calc->angle) * PI / 180);
		calc->line_bottom = (data->height / 2) + (SIZE * calc->treshold
				/ calc->tmp);
		calc->line_top = (data->height / 2) - (SIZE * calc->treshold
				/ calc->tmp);
		if (calc->line_top < 0)
			calc->line_top = 0;
		if (calc->line_bottom >= data->height)
			calc->line_bottom = data->height;
		y = (data->height / 2) + 1;
		//size_x = (int)calc->x * 64;
		while (--y > calc->line_top)
		{
			// size_y = y & (data->wood_size[0] - 1);
			// calc->color_wall = data->col_texture[size_x + size_y];
			if (data->wall_type == 'D')
				mlx_put_pixel(data->img->img_game, calc->x, y,
					calc->color_door);
			else if (data->wall_type == 'P')
				mlx_put_pixel(data->img->img_game, calc->x, y,
					calc->color_portal);
			else
				mlx_put_pixel(data->img->img_game, calc->x, y,
					calc->color_wall);
		}
		y = (data->height / 2) - 1;
		while (++y < calc->line_bottom)
		{
			// size_y = y & (data->wood_size[0] - 1);
			// calc->color_wall = data->col_texture[size_x + size_y];
			if (data->wall_type == 'D')
				mlx_put_pixel(data->img->img_game, calc->x, y,
					calc->color_door);
			else if (data->wall_type == 'P')
				mlx_put_pixel(data->img->img_game, calc->x, y,
					calc->color_portal);
			else
				mlx_put_pixel(data->img->img_game, calc->x, y,
					calc->color_wall);
		}
		t = -1;
		while (++t < calc->line_top)
			mlx_put_pixel(data->img->img_game, calc->x, t,
				data->game->color_ceiling);
		t = calc->line_bottom - 1;
		while (++t < data->height)
			mlx_put_pixel(data->img->img_game, calc->x, t,
				data->game->color_floor);
		calc->x++;
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
	while (calc.line > calc.max_lines)
	{
		data->wall_type = 'W';
		calc.distance = calc_dist(data, calc.line, &calc.direction);
		if (calc.direction == 'x')
			calc.color_wall = ft_pixel(56, 76, 200, 200);
		else
			calc.color_wall = ft_pixel(56, 76, 200, 255);
		calc.x = ((data->width / data->player->view_angle) * (calc.j));
		calc_helper(data, &calc);
		calc.angle -= 1;
		calc.j++;
		calc.line -= 1;
	}
}
