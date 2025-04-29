/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/29 10:31:51 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	wall_frame(t_entity *entity)
{
	(void)entity;
}

void	create_wall(t_list **list)
{
	t_entity	*entity;

	(void)list;
	entity = entity_new(ENTITY_WALL, NULL);
	entity->frame = wall_frame;
}
