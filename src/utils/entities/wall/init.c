/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 13:01:05 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	init_wall(t_game *game, t_ftm_window *window, t_wall *wall, char identifier)
{
	init_entity(game, window, (t_entity *)wall, identifier);
	wall->entity.type = ENTITY_WALL;
	wall->entity.frame = wall_frame;
	wall->entity.clear = clear_wall;
	wall->entity.action = wall_action;
	wall->entity.shot = wall_shot;
	wall->entity.wall = true;
	if (identifier == '1')
		identifier = '\0';
	wall->north_sprite = hashmap_get_with_identifier(game->sprites, identifier, "NO");
	wall->south_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SO");
	wall->west_sprite = hashmap_get_with_identifier(game->sprites, identifier, "WE");
	wall->east_sprite = hashmap_get_with_identifier(game->sprites, identifier, "EA");
}

t_wall	*wall_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_wall	*wall;

	wall = ft_calloc(1, sizeof(t_wall));
	if (!wall)
		return (NULL);
	init_wall(game, window, wall, identifier);
	return (wall);
}
