/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 19:54:11 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "food.h"

void	food_use(t_item *item, t_entity *user)
{
	t_food	*food;

	item_use(item, user);
	if (!user)
		return ;
	food = (t_food *)item;
	user->health += food->health;
	if (user->health > user->max_health)
		user->health = user->max_health;
}

void	clear_food(void *data)
{
	clear_item(data);
}

void	food_frame(t_item *item)
{
	item_frame(item);
}

