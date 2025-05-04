/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:42:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/04 10:52:57 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	read_map_raw_lines_e(t_map *map)
{
	int		fd;
	char	*line;
	char	**tmp_line;
	char	**tmp_map;

	fd = open(map->path, O_RDONLY);
	if (fd < 0)
		return (ft_error(ERROR_MAP_OPEN));
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (ft_str_endswith(line, "\n"))
			line[ft_strlen(line) - 1] = '\0';
		tmp_map = map->raw;
		tmp_line = ft_strvndup(&line, 1);
		map->raw = ft_strvjoin(map->raw, tmp_line);
		(ft_strvfree(tmp_map), ft_strvfree(tmp_line), free(line));
	}
	ft_close(fd);
	if (!map->raw)
		return (ft_error(ERROR_MAP_READ));
	ft_error(ERROR_NO_ERROR);
}

bool	is_map_char(char c)
{
	return (ft_isspace(c) || ft_strchr(MAP_CHARS, c));
}

void	parse_map_e(t_map *map, int argc, char **argv)
{
	if (map->initialized)
		return (ft_error(ERROR_MAP_ALREADY_INITIALIZED));
	if (argc != 2 || !argv || !argv[0] || !argv[1] || argv[2])
		return (ft_error(ERROR_INVALID_ARGS));
	if (!ft_str_endswith(argv[1], ".cub"))
		return (ft_error(ERROR_INVALID_MAP));
	map->path = argv[1];
	read_map_raw_lines_e(map);
	if (ft_has_error())
		return (ft_strvfree(map->raw), ft_bzero(map, sizeof(t_map)));
	process_raw_map_e(map);
	if (ft_has_error())
		return (ft_strvfree(map->raw), ft_hashmap_destroy(map->types),
			ft_bzero(map, sizeof(t_map)));
	set_map_size(map);
	map->initialized = true;
	ft_error(ERROR_NO_ERROR);
}

void	destroy_map(t_map *map)
{
	int	i;

	ft_strvfree(map->raw);
	ft_hashmap_destroy(map->types);
	ft_list_destroy(&map->entities);
	if (map->entity_grid)
	{
		i = -1;
		while(++i < map->size.height)
			free(map->entity_grid[i]);
		free(map->entity_grid);
	}
	ft_bzero(map, sizeof(t_map));
}
