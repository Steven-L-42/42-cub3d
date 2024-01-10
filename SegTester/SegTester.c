/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SegTester.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:08:02 by slippert          #+#    #+#             */
/*   Updated: 2024/01/10 19:17:57 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	re_open(void)
{
	const char	*prog_path = "./cub3d";
	const char	*prog_param = "maps/map.cub";
	char		command[256];

	snprintf(command, sizeof(command), "%s %s", prog_path, prog_param);
	system(command);
}

int	main(void)
{
	const char	*dir_path = "/Users/slippert/Desktop/42-cub3D/";

	if (chdir(dir_path) != 0)
	{
		perror("Fehler beim Wechseln des Verzeichnisses");
	}
	while (1)
		re_open();
	return (0);
}
