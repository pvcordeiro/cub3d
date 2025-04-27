/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:42:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 12:12:31 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	parse_map(t_map *map, int argc, char **argv)
{
	int		fd;
	char	*line;
	
	if (argc != 2 || !argv || !argv[0] || !argv[1] || argv[2])
		return (ft_error(ERROR_INVALID_ARGS));
	map->path = argv[1];
	if (!ft_str_endswith(map->path, ".cub"))
		return (ft_error(ERROR_INVALID_MAP));
	fd = open(map->path, O_RDONLY);
	if (fd < 0)
		return (ft_error(ERROR_MAP_OPEN));
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!map->raw)
			map->raw = ft_strvndup(&line, 1);
		else
			map->raw = ft_strvjoin(map->raw, ft_strvndup(&line, 1));
	}
	ft_close(fd);
}
