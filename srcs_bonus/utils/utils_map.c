/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:58:12 by jsanger           #+#    #+#             */
/*   Updated: 2024/01/17 19:55:26 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_map_height(char *input)
{
	int		count;
	int		fd;
	char	*line;

	count = 0;
	fd = open(input, O_RDONLY);
	if (fd <= 0)
		return (ft_error("Error: failed to open input!"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	return (free(line), close(fd), count);
}

int	ft_map_len(char **tmp_map)
{
	int	count;

	count = 0;
	while (tmp_map[count])
		count++;
	return (count);
}

char	*ft_strtok(char *src, char delim)
{
	char	*result;
	int		i;
	int		x;
	int		max;

	max = ft_strlen(src) + 1;
	i = 0;
	x = 0;
	while (src && i < max)
	{
		if ((src && !src[i]) || src[i] == delim)
		{
			result = ft_calloc(i + 1, 1);
			if (!result)
				return (NULL);

			while (src && src[x] && x < i)
			{;
				result[x] = src[x];
				x++;
			}
			if (result && result[0])
				return (result);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

int	ft_str_to_rgb(char *rgb_str, int *color)
{
	t_rgba	rgb;
	char	*r;
	char	*g;
	char	*b;
	int		offset;

	offset = 0;
	int count_comma = 0;
	if (ft_strlen(rgb_str) == 0)
		return (0);
		int iter = 0;
	while (rgb_str[iter])
	{
		if (rgb_str[iter++] == ',')
			count_comma++;
	}
	if (count_comma != 2)
		return (0);
	r = ft_strtok(rgb_str, ',');
	if (r == NULL)
		return (0);
	offset += ft_strlen(r) + 1;
	r = ft_strtrim_free(r, " \t\n\v\f\r");
	g = ft_strtok(rgb_str + (offset), ',');
	if (g == NULL)
		return (0);
	offset += ft_strlen(g) + 1;
	g = ft_strtrim_free(g, " \t\n\v\f\r");
	b = ft_strtok(rgb_str + (offset), ',');
	if (b == NULL)
		return (0);
	b = ft_strtrim_free(b, " \t\n\v\f\r");
	rgb.r = ft_atoi(r);
	rgb.g = ft_atoi(g);
	rgb.b = ft_atoi(b);
	if (rgb.r > 255 || rgb.g > 255 || rgb.b > 255
		|| rgb.r < 0 || rgb.g < 0 || rgb.b < 0)
		return (free(r), free(g), free(b), 0);

	*color = ft_pixel(rgb.r, rgb.g, rgb.b, 255);

	return (free(r), free(g), free(b), 1);
}
