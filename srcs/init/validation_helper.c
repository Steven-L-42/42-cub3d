/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:55:05 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/11 20:56:25 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_max_y(char **map)
{
	int	max_y;
	int	i;

	i = -1;
	max_y = 0;
	while (map[++i] != NULL)
		max_y++;
	return (max_y);
}

int	get_max_x(char **map)
{
	int	max;
	int	i;
	int	j;

	i = 0;
	max = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (j >= max)
				max = j;
			j++;
		}
		i++;
	}
	return (max);
}

void	initialize(int diff, int max_x_y[2], char **copied_map)
{
	if (diff == 0)
	{
		max_x_y[0] = get_max_x(copied_map);
		max_x_y[1] = get_max_y(copied_map);
	}
	else
	{
		max_x_y[0] += 4;
		max_x_y[1] += 4;
	}
}
