/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/10 13:43:21 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "weapon.h"

void	clear_weapon(void *data)
{
	clear_item(data);
}

void	weapon_use(t_item *item)
{
	t_weapon	*weapon;

	item_use(item);
	weapon = (t_weapon *)item;
	item->user->ammo -= weapon->ammo_usage;
	if (!item->user)
		return ;
	if (!item->user || !item->user->target_entity || !item->user->target_entity->shot)
		return ;
	item->user->target_entity->shot(item->user->target_entity, item->user);
}

void	weapon_frame(t_item *item)
{
	item->can_use = item->user && item->user->ammo - ((t_weapon *)item)->ammo_usage >= 0;
	item_frame(item);
}
