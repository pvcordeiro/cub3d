/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:42:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/28 15:52:14 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

static bool	is_map_char(char c)
{
	return (ft_isspace(c) || ft_strchr(MAP_CHARS, c));
}

static void	add_variable_to_types_e(t_hashmap *types, char *line)
{
	size_t	i;
	char	*clean_line;
	char	*key;
	char	*value;

	clean_line = ft_strtrim(line);
	i = 0;
	while (ft_isspace(clean_line[i]))
		++i;
	key = &clean_line[i];
	while (ft_isalpha(clean_line[i]))
		++i;
	if (!ft_isspace(clean_line[i]))
		return (free(clean_line), ft_error(ERROR_INVALID_TYPE));
	clean_line[i++] = '\0';
	if (ft_hashmap_get(types, key))
		return (free(clean_line), ft_error(ERROR_DUPLICATE_TYPE));
	while (ft_isspace(clean_line[i]))
		++i;
	value = ft_strdup(&clean_line[i]);
	ft_hashmap_set(types, key, value, free);
	free(clean_line);
	ft_error(ERROR_NO_ERROR);
}

static void	process_raw_map_e(t_map *map)
{
	size_t	i;

	map->types = ft_hashmap_new();
	if (!map->types)
		return (ft_error(ERROR_MAP_HASHMAP));
	i = -1;
	while (map->raw[++i])
	{
		if (ft_str_all(map->raw[i], ft_isspace))
			continue ;
		if (!ft_str_all(map->raw[i], is_map_char))
		{
			add_variable_to_types_e(map->types, map->raw[i]);
			if (ft_has_error())
				return ;
			continue ;
		}
		map->map = ft_strvdup(&map->raw[i]);
		break ;
	}
}

void	parse_map_e(t_map *map, int argc, char **argv)
{
	if (map->initialized)
		return (ft_error(ERROR_MAP_ALREADY_INITIALIZED));
	if (argc != 2 || !argv || !argv[0] || !argv[1] || argv[2])
		return (ft_error(ERROR_INVALID_ARGS));
	map->path = argv[1];
	if (!ft_str_endswith(map->path, ".cub"))
		return (ft_error(ERROR_INVALID_MAP));
	read_map_raw_lines_e(map);
	if (ft_has_error())
		return (ft_strvfree(map->raw), ft_bzero(map, sizeof(t_map)));
	process_raw_map_e(map);
	if (ft_has_error())
		return (ft_strvfree(map->raw), ft_hashmap_destroy(map->types),
			ft_bzero(map, sizeof(t_map)));
	map->initialized = true;
}

void	destroy_map(t_map *map)
{
	ft_strvfree(map->raw);
	ft_hashmap_destroy(map->types);
	ft_bzero(map, sizeof(t_map));
}
