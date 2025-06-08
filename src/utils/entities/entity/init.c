/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 14:10:41 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"

void	init_entity(t_game *game, t_ftm_window *window, t_entity *entity, char identifier)
{
	(void)window;
	if (!entity)
		return ;
	entity->type = ENTITY;
	entity->frame = entity_frame;
	entity->clear = clear_entity;
	entity->action = entity_action;
	entity->shot = entity_shot;
	entity->targetable = !ft_strequal(
		hashmap_get_with_identifier(game->map->types, identifier,
			"TARGETABLE"), "FALSE");
	entity->active = true;
	entity->hard = !ft_strequal(
		hashmap_get_with_identifier(game->map->types, identifier,
			"HARD"), "FALSE");
	entity->collision_sound = hashmap_get_with_identifier(game->sounds, identifier, "COLLISION");
	entity->identifier = identifier;
	entity->size = (t_dsize){1, 1};
	init_controller(entity, hashmap_get_with_identifier(game->map->types, identifier, "CONTROLLER"));
}

t_entity	*entity_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_entity	*entity;

	entity = ft_calloc(1, sizeof(t_entity));
	if (!entity)
		return (NULL);
	init_entity(game, window, entity, identifier);
	return (entity);
}
