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

static void	frame(t_entity *entity, double delta_time)
{
	if (entity->controller.frame)
		entity->controller.frame(entity, delta_time);
}

void	init_entity(t_game *game, t_entity *entity, char identifier)
{
	if (!entity)
		return ;
	entity->type = ENTITY;
	entity->hard = !ft_strequal(
		hashmap_get_with_identifier(game->map->types, identifier,
			"HARD"), "FALSE");
	entity->collision_sound = hashmap_get_with_identifier(game->sounds, identifier, "COLLISION");
	entity->identifier = identifier;
	entity->size = (t_dsize){1, 1};
	entity->frame = frame;
	init_controller(entity, hashmap_get_with_identifier(game->map->types, identifier, "CONTROLLER"));
	entity->key = entity->controller.key;
}
