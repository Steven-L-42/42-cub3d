/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2023/12/23 11:05:39 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_map_hight(t_map *map, char *input)
{
	int		count;
	int		fd;
	char	*line;

	count = 0;
	fd = open(input, O_RDONLY);
	line = get_next_line(fd);
	map->width = (int)ft_strlen(line);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	free(line);
	close(fd);
	return (count);
}

void	get_map(t_map *map, char *input)
{
	int		count;
	int		fd;
	char	*line;
	int		i;

	count = 0;
	fd = open(input, O_RDONLY);
	map->height = get_map_hight(map, input);
	map->map = ft_calloc(sizeof(char *), map->height + 1);
	while (count < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		map->map[count] = ft_calloc(ft_strlen(line), 1);
		i = -1;
		while (line[++i] && line[i] != '\n')
			map->map[count][i] = line[i];
		free(line);
		count++;
	}
	close(fd);
}
