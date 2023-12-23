/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/23 11:29:20 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks(void)
{
	system("leaks cub3d");
}

void	ft_running(void *param)
{
	t_data	*data;

	data = param;
	reset(data);
	calc_view(data);
	draw_player_rays(data, 90);

}

int	main(int argc, char **argv)
{
	t_map		*map;
	t_player	*player;
	t_data		*data;

	// atexit(leaks);
	data = malloc(sizeof(t_data));
	map = malloc(sizeof(t_map));
	player = malloc(sizeof(t_player));
	if (init(data, map, player, argv[1]))
		return (1);
	mlx_cursor_hook(data->mlx, update_player_angle, data);
	mlx_loop_hook(data->mlx, ft_running, data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	ft_exit(data);
}
