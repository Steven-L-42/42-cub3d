/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/04 16:05:42 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks(void)
{
	system("leaks cub3d");
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

int	ft_alloc_structs(t_data *data)
{
	data->game = malloc(sizeof(t_map));
	if (!data->game)
		return (ft_error("Error: data->game allocation failed!"));
	data->minimap = malloc(sizeof(t_minimap));
	if (!data->minimap)
		return (free(data->game), ft_error("Error: data->minimap allocation failed!"));
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (free(data->game), free(data->minimap), ft_error("Error: data->player allocation failed!"));
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		return (free(data->game), free(data->minimap), free(data->player), ft_error("Error: data->img allocation failed!"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	// atexit(leaks);
	if (argc != 2 || ft_check_extension(*(argv + 1)))
		exit(1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error("Error: data allocation failed!"));
	if (ft_alloc_structs(data))
		return (1);
	if (init(data, argv[1]))
		return (free_structs(data), 1);
	ft_instructions(data);
	write(1, "0=\n", 2);
	ft_img_to_window(data);
	write(1, "1\n", 2);
	mlx_cursor_hook(data->mlx, update_player_angle, data);
	write(1, "2\n", 2);
	mlx_loop_hook(data->mlx, ft_running, data);
	write(1, "3\n", 2);
	mlx_loop_hook(data->mlx, ft_key_hold, data);
	write(1, "4\n", 2);
	mlx_key_hook(data->mlx, ft_key_press, data);
	write(1, "5\n", 2);
	mlx_loop(data->mlx);
	exit(0);
}
