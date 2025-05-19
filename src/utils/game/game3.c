/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:10:00 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/19 21:01:07 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static bool	cmp_str_to_char(void *str, void *c)
{
	bool	result;
	char	*c_str;

	c_str = ft_strndup(c, 1);
	result = ft_strequal(str, c_str);
	return (free(c_str), result);
}

static void	create_entity_e(t_game *game, t_ftm_window *window, char c, t_size position)
{
	t_entity	*entity;

	entity = NULL;
	if (ft_list_any(game->map->identifiers.air, cmp_str_to_char, &c))
		return ;
	else if (ft_list_any(game->map->identifiers.wall, cmp_str_to_char, &c))
		entity = (t_entity *)wall_new(c, game);
	else if (ft_list_any(game->map->identifiers.player, cmp_str_to_char, &c))
		entity = (t_entity *)player_new(c);
	else if (ft_list_any(game->map->identifiers.door, cmp_str_to_char, &c))
	{
		entity = (t_entity *)door_new_e(c, window, game);
		if (fte_flagged())
			return ;
	}
	if (!entity)
		return (fte_set(ERROR_ENTITY_CREATION));
	entity->identifier = c;
	entity->coords.x = position.width;
	entity->coords.y = position.height;
	ft_list_add(&game->entities, entity, entity->free);
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
