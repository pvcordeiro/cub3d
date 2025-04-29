/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:49:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/29 14:09:10 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	create_entity_e(t_list **list, char c)
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
	ft_list_add(list, entity, entity->free);
	ft_error(ERROR_NO_ERROR);
}

void	create_entities_e(t_map *map, t_list **list)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			create_entity_e(list, map->map[i][++j]);
			if (ft_has_error())
				return ;
		}
	}
}
