/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:34:57 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/07 12:15:00 by slippert         ###   ########.fr       */
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
	ft_printf("%s\nPlayer Movement:\tW | A | S | D\n", PURPLE);
	ft_printf("Player Rotation:\tArrow Keys | Mouse\n");
	ft_printf("Player Run:\t\tLeft Shift\n");
	ft_printf("-------------------------------------------------\n");
	ft_printf("Weapon Fire:\t\tSpace | Mouse Left Button\n");
	ft_printf("Open/Close Door:\tF%s\n\n", RESET);
	ft_printf("%s\nproject by:\n\n%s", GREEN, RESET);
	ft_printf("%sjsanger:\t\033]8;;%s\033\\(Intra)\033]8;;\033\\ && ", BLUE,
		JSANGER_I);
	ft_printf("\033]8;;%s\033\\(GitHub)\033]8;;\033\\\n", JSANGER_G);
	ft_printf("%s------------------------------------\n%s", WHITE, RESET);
	ft_printf("%sslippert:\t\033]8;;%s\033\\(Intra)\033]8;;\033\\ && ", BLUE,
		SLIPPERT_I);
	ft_printf("\033]8;;%s\033\\(GitHub)\033]8;;\033\\%s\n\n", SLIPPERT_G,
		RESET);
}

int	ft_alloc_structs(t_data *data)
{
	data->game = malloc(sizeof(t_map));
	if (!data->game)
		return (free_structs(data),
			ft_error("Error: data->game allocation failed!"));
	data->minimap = malloc(sizeof(t_minimap));
	if (!data->minimap)
		return (free_structs(data),
			ft_error("Error: data->minimap allocation failed!"));
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (free_structs(data),
			ft_error("Error: data->player allocation failed!"));
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		return (free_structs(data),
			ft_error("Error: data->img allocation failed!"));
	return (0);
}

void	ft_pistol_anim(void *param)
{
	t_data	*data;
	int		i;

	data = (void *)param;
	if (data->is_shooting == true || data->img->pistol_frame > 0)
	{
		data->is_shooting = false;
		i = 0;
		while (i < 5)
		{
			if (data->img->pistol_frame == i)
				data->img->img_pistol[i++]->enabled = true;
			else
				data->img->img_pistol[i++]->enabled = false;
		}
		data->img->pistol_frame++;
		data->img->pistol_frame = data->img->pistol_frame % 5;
	}
}

// mlx_set_setting(MLX_STRETCH_IMAGE, true);
// mlx_set_setting(MLX_FULLSCREEN, true);
// atexit(leaks);
int	main(int argc, char **argv)
{
	t_data	*data;

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
	ft_img_to_window(data);
	mlx_cursor_hook(data->mlx, ft_player_angle, data);
	mlx_key_hook(data->mlx, ft_key_press, data);
	mlx_loop_hook(data->mlx, ft_key_hold, data);
	mlx_loop_hook(data->mlx, ft_running, data);
	mlx_loop_hook(data->mlx, ft_pistol_anim, data);
	mlx_mouse_hook(data->mlx, ft_mouse_press, data);
	mlx_loop(data->mlx);
	ft_exit(data);
	exit(0);
}
