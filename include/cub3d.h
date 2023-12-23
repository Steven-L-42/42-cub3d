/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:29:25 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/23 11:46:48 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/srcs/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.14159265359
# define SIZE 100

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	float			view_angle;
}					t_player;

typedef struct s_map
{
	char			**map;
	int				width;
	int				height;
}					t_map;

typedef struct s_calc_view
{
	float			temp1;
	float			temp2;
	int				j;
	int				angle;
	float			distance;
	float			tmp;
	float			linehight;
	float			linehight1;
	uint32_t		color_front;
	uint32_t		color_side;
	int				is_side;
	float			k;
	float			i;
}					t_calc_view;

typedef struct s_draw_rays
{
	uint32_t		color;
	float			angle_offset;
	float			end_x;
	float			end_y;
	int				x_coord;
	int				y_coord;
	int				i;
	int				j;
}					t_draw_rays;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_map			*map;
	t_player		*player;

	xpm_t			*texture_wall;
	xpm_t			*texture_player;
	mlx_image_t		*img_minimap;
	mlx_image_t		*img_game_wall;
	mlx_image_t		*img_player;
	mlx_image_t		*img_player_ray;
	mlx_texture_t	*text_wall;
	mlx_texture_t	*text_player;
}					t_data;

// get_map
void				get_map(t_map *map, char *input);
void				draw_minimap(t_data *data);

// utils
void				ft_free2d(char **str);
void				ft_exit(t_data *data);
void				reset(t_data *data);
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

// get_distance to wall
float				ray_distance(t_data *data, float angle);
void				calc_view(t_data *data);

void				update_player_angle(double xpos, double ypos, void *param);
void				ft_hook(void *param);

void				draw_player_rays(t_data *data, int num_rays);

int					init(t_data *data, t_map *map, t_player *player,
						char *input);

#endif
