/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:32:15 by slippert          #+#    #+#             */
/*   Updated: 2024/01/09 15:38:46 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	generate_map(t_data *data, int height, int width)
{
	int		i;
	int		j;

	height += 6;
	srand(time(NULL));
	data->game->rnd_map = ft_calloc(height + 7, sizeof(char *));
	i = 0;
	while (i < height)
		data->game->rnd_map[i++] = ft_calloc(width + 40, sizeof(char));
	i = 6;
	ft_strlcpy(data->game->rnd_map[0], NOD, ft_strlen(NOD));
	ft_strlcpy(data->game->rnd_map[1], SOD, ft_strlen(SOD));
	ft_strlcpy(data->game->rnd_map[2], WED, ft_strlen(WED));
	ft_strlcpy(data->game->rnd_map[3], EAD, ft_strlen(EAD));
	ft_strlcpy(data->game->rnd_map[4], FD, ft_strlen(FD));
	ft_strlcpy(data->game->rnd_map[5], CD, ft_strlen(CD));
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i == 6 || i == height - 1 || j == 0 || j == width - 1)
				data->game->rnd_map[i][j] = '1';
			else
			{
				if (rand() % 128 == 0)
					data->game->rnd_map[i][j] = '5';
				else if (rand() % 4 == 0)
					data->game->rnd_map[i][j] = '1';
				else
					data->game->rnd_map[i][j] = '0';
			}
			j++;
		}
		data->game->rnd_map[i][j] = '\0';
		i++;
	}
	data->game->rnd_map[(height + 6) / 2][width / 2] = 'E';
}

void	ft_create_random_map(t_data *data, char ***argv)
{
	int	fd;
	int	height;
	int	width;
	int	i;

	height = 15;
	width = 30;
	generate_map(data, height, width);
	fd = open("random.cub", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	i = 0;
	while (data->game->rnd_map[i])
	{
		write(fd, data->game->rnd_map[i], ft_strlen(data->game->rnd_map[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	(*argv)[1] = ft_strdup("random.cub");
}
