/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:25:11 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:06:46 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

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
