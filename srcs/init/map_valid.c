/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:13:31 by slippert          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:05 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_path_check(char **map, int x, int y, int rows, int cols)
{
	if (x <= 0 || x >= cols || y <= 0 || y >= rows)
		return ;
	map[y][x] = 'F';
	if (map[y + 1][x] == '0')
		ft_path_check(map, x, y + 1, rows, cols);
	if (map[y][x + 1] == '0')
		ft_path_check(map, x + 1, y, rows, cols);
	if (map[y - 1][x] == '0')
		ft_path_check(map, x, y - 1, rows, cols);
	if (map[y][x - 1] == '0')
		ft_path_check(map, x - 1, y, rows, cols);
}
int	get_max_y(char **map)
{
	int	max_y;

	max_y = 0;
	for (int i = 0; map[i] != NULL; i++)
		max_y++;
	return (max_y);
}
int	get_max_x(char **map)
{
	int	max;

	max = 0;
	for (int i = 0; map[i] != NULL; i++)
	{
		for (int j = 0; map[i][j] != '\0'; j++)
		{
			if (j >= max)
				max = j;
		}
	}
	return (max);
}
char	**allocate_big_map_0(int y, int x)
{
	char	**map;
	int		i;
	int		j;

	map = malloc((y + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < y)
	{
		j = 0;
		map[i] = malloc((x + 1) * sizeof(char));
		if (!map[i])
			return (NULL);
		while (j < x)
		{
			map[i][j] = '0';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}
bool	validate_map(char **copied_map)
{
	bool test;
	int max_x = get_max_x(copied_map);
	int max_y = get_max_y(copied_map);
	char **test_map = allocate_big_map_0(max_y + 1024, max_x + 5);
	for (int i = 0; copied_map[i] != NULL; i++)
	{
		for (int j = 0; copied_map[i][j] != '\0'; j++)
		{
			if (copied_map[i][j] == '1')
				test_map[i + 2][j + 2] = '1';
		}
	}
	ft_path_check(test_map, 4, 4, 17, 43);
	if (test_map[1][1] == 'F')
		test = true;
	else
		test = false;
	ft_free2d_char(copied_map);
	ft_free2d_char(test_map);
	return (test);
}