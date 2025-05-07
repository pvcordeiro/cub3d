/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:49:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:11:51 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static t_sprite	*get_wall_sprite(t_wall *wall, t_direction direction)
{
	if (direction == NORTH)
		return (wall->north_sprite);
	else if (direction == SOUTH)
		return (wall->south_sprite);
	else if (direction == WEST)
		return (wall->west_sprite);
	else if (direction == EAST)
		return (wall->east_sprite);
	return (NULL);
}

t_sprite	*get_entity_sprite(t_entity *entity, t_direction direction)
{
	if (entity->type == ENTITY_WALL)
		return (get_wall_sprite((t_wall *)entity, direction));
	return (NULL);
}

void	call_entity_frames(t_list *entities)
{
	t_list		*curr;
	t_entity	*entity;

	curr = entities;
	while (curr)
	{
		entity = curr->data;
		entity->frame(entity);
		curr = curr->next;
	}
}
