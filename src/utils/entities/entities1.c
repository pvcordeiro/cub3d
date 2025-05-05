/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:49:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/05 01:12:47 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	create_entity_e(t_map *map, char c, int x, int y)
{
	t_entity	*entity;

	entity = NULL;
	if (ft_isspace(c) || c == '0')
		return ;
	else if (c == '1')
		entity = entity_wall_new();
	else if (ft_strchr("NSEW", c))
		entity = entity_player_new(c);
	if (!entity)
		return (ft_error(ERROR_ENTITY_CREATION));
	entity->coords.x = x;
	entity->coords.y = y;
	ft_list_add(&map->entities, entity, entity->free);
	if (entity->type == ENTITY_PLAYER)
		cub3d()->map.player = entity;
	if (entity->hard && x >= 0 && x < cub3d()->map.size.width && y >= 0 && y <cub3d()->map.size.height)
		cub3d()->map.entity_grid[y][x] = entity;
	ft_error(ERROR_NO_ERROR);
}

void	create_entities_e(t_map *map)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			create_entity_e(map, map->map[i][j], j, i);
			if (ft_has_error())
				return ;
		}
	}
}
