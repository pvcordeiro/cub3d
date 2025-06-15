/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvcordeiro <pvcordeiro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:18:07 by pvcordeiro        #+#    #+#             */
/*   Updated: 2025/06/15 15:54:11 by pvcordeiro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	flood_fill_map(char **map, int x, int y, t_size m_size)
{
	if (x < 0 || y < 0 || x > m_size.width || y > m_size.height || !map[y]
		|| !map[y][x] || map[y][x] == 'F' || map[y][x] == '1'
		|| map[y][x] == ' ')
		return ;
	map[y][x] = 'F';
	flood_fill_map(map, x + 1, y, m_size);
	flood_fill_map(map, x - 1, y, m_size);
	flood_fill_map(map, x, y + 1, m_size);
	flood_fill_map(map, x, y - 1, m_size);
}

static bool	check_map_boundary(char **map_copy, int x, int y, t_map *map)
{
	int	dx[] = {1, -1, 0, 0};
	int	dy[] = {0, 0, 1, -1};
	int	i;

	i = -1;
	while (++i < 4)
		if (x + dx[i] < 0 || y + dy[i] < 0 || y + dy[i] >= map->size.height
			|| !map_copy[y + dy[i]][x + dx[i]] || map_copy[y + dy[i]][x
			+ dx[i]] == ' ')
			return (false);
	return (true);
}

static bool	validate_textures(t_game *game)
{
	char	*required_textures[4];
	int		i;

	required_textures[0] = "NO";
	required_textures[1] = "SO";
	required_textures[2] = "WE";
	required_textures[3] = "EA";
	i = -1;
	while (++i < 4)
		if (!ft_hashmap_get(game->sprites, (char *)required_textures[i]))
			return (false);
	return (true);
}

void	ft_backtrack_e(t_game *game)
{
	int		player_count;
	int		player_x;
	int		player_y;
	int		x;
	int		y;
	t_map	*map;
	char	**map_copy;
	char	c;

	player_count = 0;
	player_x = 0;
	player_y = 0;
	map = game->map;
	fte_set(ERROR_NO_ERROR);
	if (!validate_textures(game))
		return (fte_set(ERROR_INVALID_TYPE));
	y = -1;
	while (++y < map->size.height)
	{
		x = -1;
		while (map->map[y][++x])
		{
			c = map->map[y][x];
			if (!ft_strchr(DEFAULT_MAP_TYPES, c))
				return (fte_set(ERROR_INVALID_MAP));
			if (ft_strchr(DEFAULT_PLAYER_TYPES, c))
			{
				player_count += 1;
				player_x = x;
				player_y = y;
			}
		}
	}
	if (player_count != 1)
		return (fte_set(ERROR_INVALID_MAP));
	map_copy = ft_strvdup(map->map);
	if (!map_copy)
		return (fte_set(ERROR_MAP_ALLOC));
	map_copy[player_y][player_x] = '0';
	flood_fill_map(map_copy, player_x, player_y, map->size);
	y = -1;
	while (++y < map->size.height)
	{
		x = -1;
		while (map_copy[y][++x])
			if (map_copy[y][x] == 'F' && !check_map_boundary(map_copy, x, y,
					map))
				return (ft_strvfree(map_copy), fte_set(ERROR_INVALID_MAP));
	}
	ft_strvfree(map_copy);
}
