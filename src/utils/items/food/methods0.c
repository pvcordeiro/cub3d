/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 17:39:41 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "food.h"

void	clear_food(void *data)
{
	clear_item(data);
}

void	food_use(t_item *item)
{
	item_use(item);
	if (!item->user)
		return ;
	item->user->health += ((t_food *)item)->health;
	if (item->user->health > item->user->max_health)
		item->user->health = item->user->max_health;
	if (item->user->health < 0)
		item->user->health = 0;
}

void	food_frame(t_item *item)
{
	item->can_use = !item->last_use;
	item_frame(item);
}

