/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/27 20:56:21 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks(void)
{
	system("leaks cub3d");
}

void	img_to_window(t_data *data)
{
	mlx_image_to_window(data->mlx, data->img_player_ray, 0, 0);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	data->image->instances[0].z = 0;
}

void	ft_running(void *param)
{
	t_data	*data;

	data = param;
	reset_window(data);
	calc_view(data);
	draw_player_rays(data, 80);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	//atexit(leaks);
	data = malloc(sizeof(t_data));
	if (init(data, argv[1]))
		return (1);
	img_to_window(data);
	mlx_cursor_hook(data->mlx, update_player_angle, data);
	mlx_loop_hook(data->mlx, ft_running, data);
	mlx_loop_hook(data->mlx, ft_key_hold, data);
	mlx_key_hook(data->mlx, ft_key_press, data);
	mlx_loop(data->mlx);
	ft_exit(data);
}
