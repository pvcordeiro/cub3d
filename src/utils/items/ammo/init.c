/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 17:17:09 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ammo.h"

void	init_ammo(t_game *game, t_ftm_window *window, t_ammo *ammo,
	char identifier)
{
	if (!ammo)
		return ;
	init_item(game, window, (t_item *)ammo, identifier);
	ammo->item.clear = clear_ammo;
	ammo->item.frame = ammo_frame;
	ammo->item.use = ammo_use;
	ammo->amount = abs(ft_atoi(hashmap_get_with_identifier(game->map->types,
			identifier, "AMOUNT")));
}

t_ammo	*ammo_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_ammo	*ammo;

	ammo = ft_calloc(1, sizeof(t_ammo));
	if (!ammo)
		return (NULL);
	init_ammo(game, window, ammo, identifier);
	return (ammo);
}
