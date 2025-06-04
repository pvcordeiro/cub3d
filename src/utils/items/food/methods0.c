/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 01:13:59 by afpachec         ###   ########.fr       */
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
