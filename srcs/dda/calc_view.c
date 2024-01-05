/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:25 by slippert          #+#    #+#             */
/*   Updated: 2024/01/05 13:15:54 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calc_block_width_helper(t_data *data, t_calc_helper calc_tmp, t_calc_view *calc, bool new_block)
{
	if (new_block == true)
		calc->width_array[calc_tmp.i] = FLT_MAX;
	else
	{
		while (new_block == false)
		{
			calc_tmp.dist = calc_dist(data, calc_tmp.line, &calc->direction,
					&new_block);
			calc_tmp.angle -= 1 / calc_tmp.quality;
			calc_tmp.t++;
			calc_tmp.line -= 1 / calc_tmp.quality;
		}
	}
	if (new_block == true)
		calc->width_array[calc_tmp.i] = FLT_MAX;
	calc->width_array[calc_tmp.i] = calc_tmp.t;
	calc_tmp.i++;
	calc->width_array[calc_tmp.i] = FLT_MAX;
}

void	calc_block_width(t_data *data, t_calc_view *calc, bool new_block,
		float quality)
{
	t_calc_helper calc_tmp;


	calc_tmp.line = calc->line;
	calc_tmp.maxline = calc->max_lines;
	calc_tmp.angle = calc->angle;
	calc_tmp.t = 0;
	calc_tmp.i = 0;
	calc_tmp.quality = (float)quality;
	while (calc_tmp.line > calc_tmp.maxline)
	{
		calc_tmp.dist = calc_dist(data, calc_tmp.line, &calc->direction, &new_block);
		if (new_block == true)
		{
			calc->width_array[calc_tmp.i] = calc_tmp.t;
			calc_tmp.i++;
		}
		calc_tmp.angle -= 1 / (float)quality;
		calc_tmp.t++;
		calc_tmp.line -= 1 / (float)quality;
	}
	calc_block_width_helper(data, calc_tmp, calc, new_block);
}

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
	calc->shadow = 11;
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
	float		quality;
	float		block_width;
	bool		new_block;

	calc_preset(data, &calc);
	quality = data->width; // Need to use the width of the screen
	quality = QUALITY / (fabs(calc.max_lines) / (quality / 2));
	new_block = false;
	reset_map(data);
	calc_block_width(data, &calc, new_block, quality);
	calc.direction = '\0';
	new_block = false;
	reset_map(data);
	while (calc.line > calc.max_lines)
	{
		calc.distance = calc_dist(data, calc.line, &calc.direction, &new_block);
		draw_texture(data, &calc, new_block);
		calc.angle -= 1 / (float)quality;
		calc.j++;
		calc.line -= 1 / (float)quality;
	}
}
