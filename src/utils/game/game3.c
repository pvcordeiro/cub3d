/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:10:00 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 17:17:57 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static bool	cmp_str_to_char(void *str, void *c)
{
	bool	result;
	char	c_str[2];

	c_str[0] = *(char *)c;
	c_str[1] = '\0';
	result = ft_strequal(str, c_str);
	return (result);
}

static void	*get_creator_e(t_identifiers *identifiers, char identifier)
{
	fte_set(ERROR_NO_ERROR);
	if (ft_list_any(identifiers->air, cmp_str_to_char, &identifier))
		return (NULL);
	if (ft_list_any(identifiers->wall, cmp_str_to_char, &identifier))
		return ((void *)wall_new);
	if (ft_list_any(identifiers->player, cmp_str_to_char, &identifier))
		return ((void *)player_new);
	if (ft_list_any(identifiers->door, cmp_str_to_char, &identifier))
		return ((void *)door_new_e);
	if (ft_list_any(identifiers->billboard, cmp_str_to_char, &identifier))
		return ((void *)billboard_new);
	return (fte_set(ERROR_INVALID_IDENTIFIER_TYPE), NULL);
}


static void	create_entity_e(t_game *game, t_ftm_window *window, char c, t_size position)
{
	void		*creator;
	t_entity	*entity;

	fte_set(ERROR_NO_ERROR);
	entity = NULL;
	creator = get_creator_e(&game->map->identifiers, c);
	if (fte_flagged() || !creator)
		return ;
	entity = ((t_entity *(*)(t_game *, t_ftm_window *, char))creator)(game, window, c);
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
