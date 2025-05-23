/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/23 16:28:43 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	wall_frame(t_entity *entity, double delta_time)
{
	((void)entity, (void)delta_time);
}

static void	free_wall(void *wall)
{
	free(wall);
}

t_wall	*wall_new(char identifier, t_ftm_window *window, t_game *game)
{
	t_wall	*wall;

	(void)window;
	wall = ft_calloc(1, sizeof(t_wall));
	if (!wall)
		return (NULL);
	wall->entity.type = ENTITY_WALL;
	wall->entity.frame = wall_frame;
	wall->entity.free = free_wall;
	wall->entity.hard = true;
	wall->entity.wall = true;
	wall->entity.size = (t_size){1, 1};
	wall->entity.identifier = identifier;
	wall->north_sprite = hashmap_get_with_identifier(game->sprites, identifier, "NO");
	wall->south_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SO");
	wall->west_sprite = hashmap_get_with_identifier(game->sprites, identifier, "WE");
	wall->east_sprite = hashmap_get_with_identifier(game->sprites, identifier, "EA");
	return (wall);
}
