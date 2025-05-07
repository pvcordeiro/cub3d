/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 17:30:25 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	wall_frame(t_entity *entity)
{
	(void)entity;
}

static void	free_wall(void *entity)
{
	free(entity);
}

t_entity	*entity_wall_new(t_game *game)
{
	t_entity	*entity;

	entity = entity_new(ENTITY_WALL, NULL);
	if (!entity)
		return (NULL);
	entity->frame = wall_frame;
	entity->free = free_wall;
	entity->hard = true;
	entity->north_sprite = ft_hashmap_get_value(game->sprites, "NO");
	entity->south_sprite = ft_hashmap_get_value(game->sprites, "SO");
	entity->west_sprite = ft_hashmap_get_value(game->sprites, "WE");
	entity->east_sprite = ft_hashmap_get_value(game->sprites, "EA");
	return (entity);
}
