/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:32:15 by slippert          #+#    #+#             */
/*   Updated: 2024/01/09 20:25:59 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	generate_map_preset(t_data *data, int height, int width)
{
	int	i;
	int	j;

	data->game->rnd_map = ft_calloc(height + 1, sizeof(char *));
	i = 0;
	while (i < height)
		data->game->rnd_map[i++] = ft_calloc(width + 40, sizeof(char));
	ft_strlcpy(data->game->rnd_map[0], NOD, ft_strlen(NOD));
	ft_strlcpy(data->game->rnd_map[1], SOD, ft_strlen(SOD));
	ft_strlcpy(data->game->rnd_map[2], WED, ft_strlen(WED));
	ft_strlcpy(data->game->rnd_map[3], EAD, ft_strlen(EAD));
	ft_strlcpy(data->game->rnd_map[4], FD, ft_strlen(FD));
	ft_strlcpy(data->game->rnd_map[5], CD, ft_strlen(CD));
}

static void	generate_map_helper(t_data *data, int i, int j)
{
	if (rand() % 128 == 0)
		data->game->rnd_map[i][j] = '5';
	else if (rand() % 4 == 0)
		data->game->rnd_map[i][j] = '1';
	else
		data->game->rnd_map[i][j] = '0';
}

static void	ft_set_player_pos(t_data *data, int height, int width)
{
	char	pos;
	int		player_height;
	int		player_width;

	player_height = rand() % ((height - 2) - 7 + 1) + 7;
	player_width = rand() % ((width - 2) - 1 + 1) + 1;
	if (player_height > height / 2 && ft_differ(player_height, height
			/ 2) >= ft_differ(player_width, width / 2))
		pos = 'N';
	else if (player_height < height / 2 && ft_differ(player_height, height
			/ 2) >= ft_differ(player_width, width / 2))
		pos = 'S';
	else if (player_width < width / 2 && ft_differ(player_width, width
			/ 2) >= ft_differ(player_height, height / 2))
		pos = 'E';
	else
		pos = 'W';
	data->game->rnd_map[player_height][player_width] = pos;
	data->game->is_random_map = true;
}

static void	generate_map(t_data *data, int height, int width)
{
	int	i;
	int	j;

	generate_map_preset(data, height, width);
	i = 6;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i == 6 || i == height - 1 || j == 0 || j == width - 1)
				data->game->rnd_map[i][j] = '1';
			else
				generate_map_helper(data, i, j);
			j++;
		}
		data->game->rnd_map[i][j] = '\0';
		i++;
	}
	ft_set_player_pos(data, height, width);
}

void	ft_create_random_map(t_data *data, char ***argv)
{
	int	fd;
	int	height;
	int	width;
	int	i;

	srand(time(NULL));
	height = (10 + rand() % (20 - 10 + 1)) + 6;
	width = 10 + rand() % (35 - 10 + 1);
	generate_map(data, height, width);
	fd = open("random.cub", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	i = 0;
	while (data->game->rnd_map[i])
	{
		write(fd, data->game->rnd_map[i], ft_strlen(data->game->rnd_map[i]));
		if (data->game->rnd_map[i + 1])
			write(fd, "\n", 1);
		i++;
	}
	close(fd);
	(*argv)[1] = ft_strdup("random.cub");
}
