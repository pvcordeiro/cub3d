/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 22:58:57 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	wall_frame(t_entity *entity)
{
	(void)entity;
}

static void	free_wall(void *wall)
{
	free(wall);
}

t_wall	*wall_new(t_game *game)
{
	t_wall	*wall;

	wall = ft_calloc(1, sizeof(t_wall));
	if (!wall)
		return (NULL);
	wall->base.type = ENTITY_WALL;
	wall->base.frame = wall_frame;
	wall->base.free = free_wall;
	wall->base.hard = true;
	wall->north_sprite = ft_hashmap_get_value(game->sprites, "NO");
	wall->south_sprite = ft_hashmap_get_value(game->sprites, "SO");
	wall->west_sprite = ft_hashmap_get_value(game->sprites, "WE");
	wall->east_sprite = ft_hashmap_get_value(game->sprites, "EA");
	return (wall);
}
