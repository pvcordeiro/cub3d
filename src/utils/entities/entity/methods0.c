/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 13:09:39 by paude-so         ###   ########.fr       */
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

void	entity_shot(t_entity *shooted, t_entity *shooter)
{
	t_weapon	*weapon;

	if (!shooted || !shooter)
		return ;
	weapon = (t_weapon *)shooter->inventory[shooter->inventory_index];
	if (!weapon->item.weapon)
		return ;
	shooted->health -= weapon->damage;
	if (shooted->health < 0)
		shooted->health = 0;
}
