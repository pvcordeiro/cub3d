/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:42:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/28 18:06:34 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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

void	process_raw_map_e(t_map *map)
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
