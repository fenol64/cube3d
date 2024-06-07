/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:08:56 by fnascime          #+#    #+#             */
/*   Updated: 2024/06/07 15:38:47 by aldantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube.h"

int	get_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	printf("fd: %d\n", fd);
	return (fd);
}

void	finish_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
