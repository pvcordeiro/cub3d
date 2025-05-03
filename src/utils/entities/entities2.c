/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:25:11 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/03 15:44:09 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

t_entity	*entity_new(t_entity_type type, void *private)
{
	t_entity	*entity;

	entity = ft_calloc(1, sizeof(t_entity));
	if (!entity)
		return (NULL);
	entity->type = type;
	entity->private = private;
	return (entity);
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
