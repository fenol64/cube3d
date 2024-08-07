/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:11:16 by fnascime          #+#    #+#             */
/*   Updated: 2024/08/07 03:53:54 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube.h"

int	validate_args(int c, char **v)
{
	if (c != 2)
	{
		handle_errors("Invalid number of arguments");
		return (FALSE);
	}
	if (ft_strncmp(v[1] + ft_strlen(v[1]) - 4, ".cub", 4) != 0)
	{
		handle_errors("Invalid file extension");
		return (FALSE);
	}
	return (TRUE);
}

t_bool	validate_color(char *line)
{
	char	**color;
	int		i;
	int		j;

	i = 0;
	j = 0;
	color = ft_split(line, ',');
	while (color[i])
	{
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j]))
				break ;
			j++;
		}
		i++;
	}
	ft_free_matrix(color);
	if (i != 3)
		return (FALSE);
	return (TRUE);
}

int	validate_arg(char *line, t_map_args *map_args)
{
	if (validate_colors(line, map_args) || validate_textures(line, map_args))
		return (TRUE);
	else
	{
		handle_errors("Invalid argument");
		if (map_args->c)
			free(map_args->c);
		if (map_args->f)
			free(map_args->f);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	validated_all_args(t_map_args map_args)
{
	if (map_args.f && map_args.c && map_args.no && map_args.so && map_args.we
		&& map_args.ea)
		return (TRUE);
	return (FALSE);
}

t_bool	validate_file_args(char *file_path, t_cube *cube)
{
	char	*line;
	int		fd;

	fd = get_file(file_path);
	line = get_next_line(fd);
	while (!cube->validated_args && line)
	{
		if (validated_all_args(cube->map_args))
		{
			cube->validated_args = TRUE;
			break ;
		}
		if (*line != '\n')
			if (!validate_arg(line, &cube->map_args))
				break ;
		free(line);
		line = get_next_line(fd);
		cube->map_index++;
	}
	free(line);
	finish_file(fd);
	if (cube->validated_args)
		return (TRUE);
	free_map_args(&cube->map_args);
	return (handle_errors("Invalid arguments"), FALSE);
}
