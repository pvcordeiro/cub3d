/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:10:00 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 22:52:38 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	create_entity_e(t_game *game, t_ftm_window *window, char c, t_size position)
{
	t_entity_creator	creator;
	t_entity			*entity;

	fte_set(ERROR_NO_ERROR);
	entity = NULL;
	creator = get_entity_creator(&game->map->identifiers, c);
	if (fte_flagged() || !creator)
		return ;
	entity = creator(game, window, c);
	if (fte_flagged())
		return ;
	if (!entity)
		return (fte_set(ERROR_ENTITY_CREATION));
	entity->identifier = c;
	entity->coords.x = position.width;
	entity->coords.y = position.height;
	if (entity->billboard)
	{
		entity->coords.x += 0.5 - entity->size.width * 0.5;
 		entity->coords.y += 0.5 - entity->size.height * 0.5;
	}
	ft_list_add(&game->entities, entity, free_entity);
	if (entity->type == ENTITY_PLAYER)
		game->player = (t_player *)entity;
	fte_set(ERROR_NO_ERROR);
}

void	init_entities_e(t_game *game, t_ftm_window *window)
{
	t_size	s;

	s.height = -1;
	while (game->map->map[++s.height])
	{
		s.width = -1;
		while (game->map->map[s.height][++s.width])
		{
			if (create_entity_e(game, window, game->map->map[s.height][s.width], s), fte_flagged())
				return ;
			if (fte_flagged())
				return ;
		}
	}
}
