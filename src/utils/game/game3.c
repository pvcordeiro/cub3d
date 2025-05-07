/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:10:00 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:10:26 by afpachec         ###   ########.fr       */
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
		return (ft_error(ERROR_ENTITY_CREATION));
	entity->coords.x = x;
	entity->coords.y = y;
	ft_list_add(&game->entities, entity, entity->free);
	if (entity->type == ENTITY_PLAYER)
		game->player = (t_player *)entity;
	if (entity->hard && x >= 0 && x < game->map->size.width && y >= 0 && y < game->map->size.height)
		game->entity_grid[y][x] = entity;
	ft_error(ERROR_NO_ERROR);
}

void	init_entities_e(t_game *game)
{
	int	i;
	int	j;

	game->entity_grid = ft_calloc(game->map->size.height, sizeof(t_entity **));
	if (!game->entity_grid)
		return (ft_error(ERROR_INIT_MAP_GRID_TRIPLE));
	i = -1;
	while (++i < game->map->size.height)
	{
		game->entity_grid[i] = ft_calloc(game->map->size.width, sizeof(t_entity *));
		if (!game->entity_grid[i])
			return (ft_strvfree((char **)game->entity_grid), ft_error(ERROR_INIT_MAP_GRID_DOUBLE));
	}
	i = -1;
	while (game->map->map[++i])
	{
		j = -1;
		while (game->map->map[i][++j])
		{
			create_entity_e(game, game->map->map[i][j], j, i);
			if (ft_has_error())
				return ;
		}
	}
}
