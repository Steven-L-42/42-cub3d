/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:49:49 by slippert          #+#    #+#             */
/*   Updated: 2023/12/25 09:58:24 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Funktion: ray_preset
// Zweck: Initialisiert die notwendigen Werte für die Raycasting-Berechnungen.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - ray: Zeiger auf die Struktur,
//	die Informationen über die zu zeichnenden Rays enthält.
//   - num_rays: Die Anzahl der Rays, die gezeichnet werden sollen.
//
// Die Funktion setzt den Bildspeicher für Spieler-Rays auf Null,
// wählt eine Standardfarbe für die Rays
// und initialisiert den Startwinkel für die Berechnungen.
void	ray_preset(t_data *data, t_draw_rays *ray, int num_rays)
{
	ft_memset(data->img_player_ray->pixels, 0, data->img_player_ray->width
		* data->img_player_ray->height * sizeof(int32_t));
	ray->color = ft_pixel(0, 255, 128, 255);
	ray->i = -num_rays / 2;
}

// Funktion: ray_helper
// Zweck: Hilfsfunktion für die Berechnung und Darstellung einzelner Rays.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - ray: Zeiger auf die Struktur,
//	die Informationen über die zu zeichnenden Rays enthält.
//
// Die Funktion iteriert über eine maximale Anzahl von Schritten, um die
// Koordinaten jedes einzelnen Rays zu berechnen. Sie überprüft dann,
// ob die berechneten Koordinaten im gültigen Bereich liegen und ob es
// Kollisionen mit Wänden gibt. Bei gültigen Koordinaten wird die
// entsprechende Pixelposition im Bildspeicher markiert.
void	ray_helper(t_data *data, t_draw_rays *ray)
{
	while (ray->j < INT_MAX / 2)
	{
		ray->x_coord = data->player->x * 16 + 8 + ray->j
			* cos((data->player->angle + ray->angle_offset) * PI / 180);
		ray->y_coord = data->player->y * 16 + 8 + ray->j
			* sin((data->player->angle + ray->angle_offset) * PI / 180);
		if (ray->x_coord >= 0 && ray->y_coord >= 0
			&& ray->x_coord < data->img_player_ray->width
			&& ray->y_coord < data->img_player_ray->height)
		{
			if (data->map->map[ray->y_coord / 16][ray->x_coord / 16] == '1')
				break ;
			mlx_put_pixel(data->img_player_ray, ray->x_coord, ray->y_coord,
				ray->color);
		}
		ray->j++;
	}
}

// Funktion: draw_player_rays
// Zweck: Zeichnet alle Rays vom Spieler aus und zeigt das Ergebnis im Fenster an.
// Parameter:
//   - data: Zeiger auf die Datenstruktur, die Informationen zum Spiel enthält.
//   - num_rays: Die Anzahl der Rays, die gezeichnet werden sollen.
//
// Die Funktion iteriert über alle Rays und berechnet deren Positionen und Endpunkte.
// Für jeden Ray wird dann die Hilfsfunktion ray_helper aufgerufen, die
// die Berechnungen für einzelne Rays durchführt. Das Ergebnis wird im Fenster angezeigt.
void	draw_player_rays(t_data *data, int num_rays)
{
	t_draw_rays	ray;

	ray_preset(data, &ray, num_rays);
	while (ray.i <= num_rays / 2)
	{
		ray.angle_offset = ray.i;
		ray.end_x = data->player->x * 16 + 8 * cos((data->player->angle
					+ ray.angle_offset) * PI / 180);
		ray.end_y = data->player->y * 16 + 8 * sin((data->player->angle
					+ ray.angle_offset) * PI / 180);
		ray.j = 0;
		ray_helper(data, &ray);
		ray.i++;
	}
	mlx_image_to_window(data->mlx, data->img_player_ray, 0, 0);
}
