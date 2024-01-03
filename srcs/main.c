/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/02 19:51:38 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks(void)
{
	system("leaks cub3d");
}

void	ft_img_to_window(t_data *data)
{
	mlx_image_to_window(data->mlx, data->img->img_player_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->img->img_game, 0, 0);
	data->img->img_game->instances[0].z = 0;
}

static void	reset_window(t_data *data)
{
	ft_memset(data->img->img_game->pixels, 0, data->img->img_game->width
		* data->img->img_game->height * sizeof(int32_t));
}

void	ft_running(void *param)
{
	t_data	*data;

	data = param;
	reset_window(data);
	calc_view(data);
	draw_player_rays(data, 80);
}

void	ft_instructions(t_data *data)
{
	int	i;

	i = 0;
	write(1, "\n", 1);
	while (data->game->map[i])
		ft_printf("%s\n", data->game->map[i++]);
	ft_printf("%s\nPlayer Movement:\tWASD\n", PURPLE);
	ft_printf("Player Rotation:\tArrow Keys | Mouse\n");
	ft_printf("Open/Close Door:\tC\n%s", RESET);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	// atexit(leaks);
	data = malloc(sizeof(t_data));
	data->game = malloc(sizeof(t_map));
	data->minimap = malloc(sizeof(t_minimap));
	data->player = malloc(sizeof(t_player));
	if (init(data, argv[1]))
		return (1);
	ft_instructions(data);
	ft_img_to_window(data);
	mlx_cursor_hook(data->mlx, update_player_angle, data);
	mlx_loop_hook(data->mlx, ft_running, data);
	mlx_loop_hook(data->mlx, ft_key_hold, data);
	mlx_key_hook(data->mlx, ft_key_press, data);
	mlx_loop(data->mlx);
	exit(0);
}
