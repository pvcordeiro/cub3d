/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:10:00 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/08 16:31:01 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	create_entity_e(t_game *game, char c, int x, int y)
{
	t_entity	*entity;

	entity = NULL;
	if (ft_isspace(c) || c == '0')
		return ;
	else if (c == '1')
		entity = (t_entity *)wall_new(game);
	else if (ft_strchr("NSEW", c))
		entity = (t_entity *)player_new(c);
	if (!entity)
		return (fte_set(ERROR_ENTITY_CREATION));
	entity->coords.x = x;
	entity->coords.y = y;
	ft_list_add(&game->entities, entity, entity->free);
	if (entity->type == ENTITY_PLAYER)
		game->player = (t_player *)entity;
	if (entity->type == ENTITY_WALL && x >= 0 && x < game->map->size.width
		&& y >= 0 && y < game->map->size.height)
		game->wall_grid[y][x] = (t_wall *)entity;
	fte_set(ERROR_NO_ERROR);
}

void	init_entities_e(t_game *game)
{
	t_size	s;

	game->wall_grid = ft_calloc(game->map->size.height, sizeof(t_entity **));
	if (!game->wall_grid)
		return (fte_set(ERROR_INIT_MAP_GRID_TRIPLE));
	s.height = -1;
	while (++s.height < game->map->size.height)
	{
		game->wall_grid[s.height] = ft_calloc(game->map->size.width,
				sizeof(t_entity *));
		if (!game->wall_grid[s.height])
			return (ft_strvfree((char **)game->wall_grid),
				fte_set(ERROR_INIT_MAP_GRID_DOUBLE));
	}
	s.height = -1;
	while (game->map->map[++s.height])
	{
		s.width = -1;
		while (game->map->map[s.height][++s.width])
		{
			if (create_entity_e(game, game->map->map[s.height][s.width],
				s.width, s.height), fte_flagged())
				return ;
		}
	}
}
