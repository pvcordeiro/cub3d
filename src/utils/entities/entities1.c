/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:49:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/03 12:56:49 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	create_entity_e(t_list **list, char c, int x, int y)
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
	ft_list_add(list, entity, entity->free);
	if (entity->type == ENTITY_PLAYER)
		cub3d()->map.player = entity;
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
			create_entity_e(&map->entities, map->map[i][j], j, i);
			if (ft_has_error())
				return ;
		}
	}
}
