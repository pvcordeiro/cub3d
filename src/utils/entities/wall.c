/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/29 14:01:57 by afpachec         ###   ########.fr       */
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

t_entity	*entity_wall_new(void)
{
	t_entity	*entity;

	entity = entity_new(ENTITY_WALL, NULL);
	if (!entity)
		return (NULL);
	entity->frame = wall_frame;
	entity->free = free_wall;
	return (entity);
}
