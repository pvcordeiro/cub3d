/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 19:57:20 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"

void	entity_frame(t_entity *entity, double delta_time)
{
	int	i;

	if (entity->controller.frame)
		entity->controller.frame(entity, delta_time);
	i = -1;
	while (++i < INVENTORY_SIZE)
		if (entity->inventory[i] && entity->inventory[i]->frame)
			entity->inventory[i]->frame(entity->inventory[i]);
}

void	clear_entity(void *entity)
{
	(void)entity;
}

void	entity_action(t_entity *entity, t_entity *actioner)
{
	((void)entity, (void)actioner);
}
