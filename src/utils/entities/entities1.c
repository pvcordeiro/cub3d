/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:49:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 20:36:00 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	create_entity_e(t_game *game, char c, int x, int y)
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
	ft_list_add(&game->entities, entity, entity->free);
	if (entity->type == ENTITY_PLAYER)
		game->player = entity;
	if (entity->hard && x >= 0 && x < game->map->size.width && y >= 0 && y < game->map->size.height)
		game->entity_grid[y][x] = entity;
	ft_error(ERROR_NO_ERROR);
}

void	create_entities_e(t_game *game)
{
	int	i;
	int	j;

	game->entity_grid = ft_calloc(game->map->size.height, sizeof(t_entity **));
	if (!game->entity_grid)
		return ;
	i = -1;
	while (++i < game->map->size.height)
	{
		game->entity_grid[i] = ft_calloc(game->map->size.width, sizeof(t_entity *));
		if (!game->entity_grid[i])
			return ;
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

t_sprite	*get_entity_sprite(t_entity *entity, t_direction direction)
{
	if (direction == NORTH)
		return (entity->north_sprite);
	else if (direction == SOUTH)
		return (entity->south_sprite);
	else if (direction == WEST)
		return (entity->west_sprite);
	else if (direction == EAST)
		return (entity->east_sprite);
	return (NULL);
}
