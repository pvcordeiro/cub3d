/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/22 14:37:18 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

void	init_entity(t_game *game, t_entity *entity, char identifier)
{
	if (!entity)
		return ;
	entity->type = ENTITY;
	entity->hard = !ft_strequal(
		hashmap_get_with_identifier(game->map->types, identifier,
			"HARD"), "FALSE");
	entity->identifier = identifier;
	entity->size = (t_size){1, 1};
}
