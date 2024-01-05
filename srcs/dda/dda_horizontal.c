/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_horizontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:00:25 by slippert          #+#    #+#             */
/*   Updated: 2024/01/05 14:54:12 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calc_block_width_helper(t_data *data, t_dda_helper dda_tmp, t_dda *dda,
		bool new_block)
{
	if (new_block == true)
		dda->width_array[dda_tmp.i] = FLT_MAX;
	else
	{
		while (new_block == false)
		{
			dda_tmp.dist = dda_dist(data, dda_tmp.line, &dda->direction,
					&new_block);
			dda_tmp.angle -= 1 / dda_tmp.quality;
			dda_tmp.t++;
			dda_tmp.line -= 1 / dda_tmp.quality;
		}
	}
	if (new_block == true)
		dda->width_array[dda_tmp.i] = FLT_MAX;
	dda->width_array[dda_tmp.i] = dda_tmp.t;
	dda_tmp.i++;
	dda->width_array[dda_tmp.i] = FLT_MAX;
}

void	calc_block_width(t_data *data, t_dda *dda, bool new_block,
		float quality)
{
	t_dda_helper	dda_tmp;

	dda_tmp.line = dda->line;
	dda_tmp.maxline = dda->max_lines;
	dda_tmp.angle = dda->angle;
	dda_tmp.t = 0;
	dda_tmp.i = 0;
	dda_tmp.quality = (float)quality;
	while (dda_tmp.line > dda_tmp.maxline)
	{
		dda_tmp.dist = dda_dist(data, dda_tmp.line, &dda->direction,
				&new_block);
		if (new_block == true)
		{
			dda->width_array[dda_tmp.i] = dda_tmp.t;
			dda_tmp.i++;
		}
		dda_tmp.angle -= 1 / (float)quality;
		dda_tmp.t++;
		dda_tmp.line -= 1 / (float)quality;
	}
	calc_block_width_helper(data, dda_tmp, dda, new_block);
}

// Funktion: calc_preset
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - calc: Zeiger auf die Struktur,
//		die Informationen für die Berechnungen enthält.
//
// Die Funktion setzt verschiedene Werte wie Winkel, Farben und Zählvariablen
// für die Berechnungen der Sichtlinien. Zudem wird der bestehende Bildspeicher
// gelöscht und ein neuer Bildspeicher für die Sichtlinien erstellt.
void	calc_preset(t_data *data, t_dda *dda)
{
	dda->j = 0;
	dda->max_lines = -(data->player->view_angle / 2);
	dda->temp2 = -dda->max_lines;
	dda->angle = -dda->max_lines;
	dda->color_wall = ft_pixel(56, 76, 200, 255);
	dda->color_door = ft_pixel(125, 76, 56, 255);
	dda->color_portal = ft_pixel(56, 125, 125, 255);
	dda->line = dda->max_lines * -1;
	dda->treshold = (float)6.2f * (data->width / 1920.0);
	dda->direction = '\0';
	dda->shadow = 11;
}

// Funktion: calc_view
// Zweck: Berechnet und zeichnet die Sichtlinien im Spiel.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//
// Die Funktion initialisiert die notwendigen Werte, iteriert über die
// Sichtlinien und ruft die Hilfsfunktion calc_helper für jede Sichtlinie auf.
// Das Ergebnis wird im Fenster angezeigt.
void	dda_horizontal(t_data *data)
{
	t_dda	dda;
	float	quality;
	bool	new_block;

	calc_preset(data, &dda);
	quality = data->width;
	quality = QUALITY / (fabs(dda.max_lines) / (quality / 2));
	new_block = false;
	reset_map(data);
	calc_block_width(data, &dda, new_block, quality);
	dda.direction = '\0';
	new_block = false;
	while (dda.line > dda.max_lines)
	{
		dda.distance = dda_dist(data, dda.line, &dda.direction, &new_block);
		dda_vertical(data, &dda, new_block);
		dda.angle -= 1 / (float)quality;
		dda.j++;
		dda.line -= 1 / (float)quality;
	}
}
