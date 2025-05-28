/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/28 20:01:44 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

void	init_wall(t_game *game, t_wall *wall, char identifier)
{
	init_entity(game, (t_entity *)wall, identifier);
	wall->entity.type = ENTITY_WALL;
	wall->entity.wall = true;
	wall->north_sprite = hashmap_get_with_identifier(game->sprites, identifier, "NO");
	wall->south_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SO");
	wall->west_sprite = hashmap_get_with_identifier(game->sprites, identifier, "WE");
	wall->east_sprite = hashmap_get_with_identifier(game->sprites, identifier, "EA");
}

t_wall	*wall_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_wall	*wall;

	(void)window;
	wall = ft_calloc(1, sizeof(t_wall));
	if (!wall)
		return (NULL);
	init_wall(game, wall, identifier);
	wall->entity.free = free;
	return (wall);
}
