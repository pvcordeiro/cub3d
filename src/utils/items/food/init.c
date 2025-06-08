/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 16:12:08 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "food.h"

void	init_food(t_game *game, t_ftm_window *window, t_food *food,
	char identifier)
{
	if (!food)
		return ;
	init_item(game, window, (t_item *)food, identifier);
	food->item.food = true;
	food->item.clear = clear_food;
	food->item.frame = food_frame;
	food->item.use = food_use;
	food->health = fabs(ft_atof(hashmap_get_with_identifier(game->map->types,
			identifier, "HEALTH")));
}

t_food	*food_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_food	*food;

	food = ft_calloc(1, sizeof(t_food));
	if (!food)
		return (NULL);
	init_food(game, window, food, identifier);
	return (food);
}
