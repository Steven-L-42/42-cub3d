/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/29 13:17:41 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	**ft_fill_tmp(char **tmp_map, int fd)
{
	char	*line;
	int		y;
	int		x;

	y = -1;
	line = get_next_line(fd);
	while (line)
	{
		x = 0;
		if (line && line[x] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		tmp_map[++y] = ft_calloc(ft_strlen(line) + 1, 1);
		if (!tmp_map[y])
			return (ft_error("Error: tmp_map[y] allocation failed!"), NULL);
		x = -1;
		while (line[++x] && line[x] != '\n')
			tmp_map[y][x] = line[x];
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), tmp_map);
}

static int	ft_get_text(char **tmp_map, char *(*texture), char *needle)
{
	int	found;
	int	y;
	int	max_y;

	max_y = 0;
	while (tmp_map[max_y])
		max_y++;
	y = 0;
	*texture = NULL;
	while (!*texture && y < max_y)
	{
		*texture = ft_strnstr(tmp_map[y], needle, ft_strlen(tmp_map[y]));
		y++;
	}
	if (!*texture)
		return (0);
	*texture = ft_strtrim_free(*texture, needle);
	*texture = ft_strtrim_free(*texture, " \t\n\v\f\r");
	return (1);
}

static int	ft_fill_map(t_map *game, char **tmp_map)
{
	int		y_game;
	int		max_y;
	int		x;

	max_y = ft_map_len(tmp_map);
	y_game = 0;
	game->map = ft_calloc(max_y, sizeof(char *));
	if (!game->map)
		return (ft_error("Error: game->map allocation failed!"));
	while (tmp_map && tmp_map[y_game + 6])
	{
		x = -1;
		game->map[y_game] = ft_calloc(ft_strlen(tmp_map[y_game + 6]) + 1, 1);
		if (!game->map[y_game])
			return (ft_error("Error: game->map[y_game] allocation failed!"));
		while (tmp_map[y_game + 6][++x])
			game->map[y_game][x] = tmp_map[y_game + 6][x];
		if (game->width < ft_strlen(game->map[y_game]))
			game->width = ft_strlen(game->map[y_game]);
		y_game++;
	}
	game->height = y_game;
	return (0);
}

int	get_map(t_map *game, char *input)
{
	int		fd;
	char	**tmp_map;

	fd = open(input, O_RDONLY);
	if (!fd)
		return (ft_error("Error: failed to open input!"));
	tmp_map = ft_calloc(get_map_height(input) + 1, sizeof(char *));
	if (!tmp_map)
		return (close(fd), ft_error("Error: tmp_map allocation failed!"));
	tmp_map = ft_fill_tmp(tmp_map, fd);
	if (!tmp_map)
		return (1);
	if (ft_get_text(tmp_map, &game->NO, "NO")
		* ft_get_text(tmp_map, &game->SO, "SO")
		* ft_get_text(tmp_map, &game->WE, "WE")
		* ft_get_text(tmp_map, &game->EA, "EA")
		* ft_get_text(tmp_map, &game->F, "F")
		* ft_get_text(tmp_map, &game->C, "C") == 0)
		return (ft_free2d(tmp_map), ft_error("Error: Texture parsing!"));
	if (ft_str_to_rgb(game->F, &game->color_floor)
		* ft_str_to_rgb(game->C, &game->color_ceiling) == 0)
		return (ft_free2d(tmp_map), ft_error("Error: Color parsing!"));
	if (ft_fill_map(game, tmp_map))
		return (ft_free2d(tmp_map), 1);
	return (ft_free2d(tmp_map), close(fd), 0);
}
// for (int i = 0; tmp_map[i]; i++)
// 	printf("%s\n", tmp_map[i]);
// printf("\n");
// printf("%s\n", game->NO);
// printf("%s\n", game->SO);
// printf("%s\n", game->WE);
// printf("%s\n", game->EA);
// printf("%s\n", game->F);
// printf("%s\n", game->C);
// printf("\n");
// for (int i = 0; game->map[i]; i++)
// 	printf("%s\n", game->map[i]);