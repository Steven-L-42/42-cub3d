/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:29:25 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/27 20:55:20 by slippert         ###   ########.fr       */
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
	float			prev_angle;
	float			view_angle;
	double			prev_time;
	int				mouse_x;
	int				mouse_y;
	float			prev_mouseX;
	char			start_direction;
}					t_player;

typedef struct s_map
{
	char			**map;
	int				width;
	int				height;
}					t_map;

typedef struct s_minimap
{
	int				**doors;
	int				width;
	int				height;
}					t_minimap;

typedef struct s_calc_view
{
	float			max_lines;
	float			temp2;
	float			j;
	float			angle;
	double			distance;
	float			tmp;
	double			line_bottom;
	double			line_top;
	uint32_t		color_floor;
	uint32_t		color_ceiling;
	uint32_t		color_wall;
	uint32_t		color_door;
	uint32_t		color_portal;
	int				is_side;
	float			line;
	float			x;
}					t_calc_view;

typedef struct s_draw_rays
{
	int				color;
	float			angle_offset;
	float			end_x;
	float			end_y;
	int				x_coord;
	int				y_coord;
	float			i;
}					t_draw_rays;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_map			*map;
	t_minimap		*minimap;
	t_player		*player;

	xpm_t			*texture_wall;
	xpm_t			*texture_player;
	mlx_image_t		*img_minimap;
	mlx_image_t		*img_mm_wall;
	mlx_image_t		*img_mm_wall_shadow;
	mlx_image_t		*img_mm_portal;
	mlx_image_t		*img_mm_door_closed;
	mlx_image_t		*img_mm_door_open;
	mlx_image_t		*img_game_cursor;
	mlx_image_t		*img_player;
	mlx_image_t		*img_player_ray;
	mlx_image_t		*img_game_wall;
	uint32_t		*col_wood;
	mlx_texture_t	*text_wood;
	int				wood_size[2];
	char			*wood[1024];
	char			key[64];
	uint32_t		color[64];
	int				wall_height;
	float			ray_y;
	float			ray_x;
	int				width;
	int				height;
	char			wall_type;
}					t_data;

// get_map
void				get_map(t_map *map, char *input);
void				draw_minimap(t_data *data);

// init_1
int					init(t_data *data, char *input);

// init_2
void				init_coords(t_data *data, int pixel_x, int pixel_y);
void				init_player(t_data *data);

// utils basic
void				ft_free2d(char **str);
void				ft_exit(t_data *data);
void				reset_window(t_data *data);
int					ft_is_in_set(char c, char *set);
// utils color
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int					get_colour_from_pixel(u_int8_t *pixel);
void				hex_to_rgb(char *hex, int *r, int *g, int *b);
uint32_t			*get_color(mlx_texture_t *texture);

// get_distance to wall
double				ray_distance(t_data *data, float angle);
void				calc_view(t_data *data);

void				update_player_angle(double xpos, double ypos, void *param);

// hotkeys
void				ft_key_hold(void *param);
void				ft_key_press(mlx_key_data_t keydata, void* param);

void				draw_player_rays(t_data *data, int num_rays);

#endif
