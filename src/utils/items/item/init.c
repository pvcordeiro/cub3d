/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 19:52:15 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "item.h"

void	init_item(t_game *game, t_ftm_window *window, t_item *item,
	char identifier)
{
	(void)window;
	if (!item)
		return ;
	item->use = item_use;
	item->clear = clear_item;
	item->identifier = identifier;
	item->name = hashmap_get_with_identifier(game->map->types, identifier,
		"NAME");
	item->description = hashmap_get_with_identifier(game->map->types,
		identifier, "DESCRIPTION");
	item->icon_still_sprite = hashmap_get_with_identifier(game->sprites,
		identifier, "ICON_SPRITE");
	item->screen_still_sprite = hashmap_get_with_identifier(game->sprites,
		identifier, "SCREEN_SPRITE");
	item->screen_use_sprite = hashmap_get_with_identifier(game->sprites,
		identifier, "SCREEN_USE_SPRITE");
	item->icon_use_sprite = hashmap_get_with_identifier(game->sprites,
		identifier, "ICON_USE_SPRITE");
	item->use_sound = hashmap_get_with_identifier(game->sounds,
		identifier, "USE");
	item->icon_sprite = item->icon_still_sprite;
	item->screen_sprite = item->screen_still_sprite;
}

t_item	*item_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_item	*item;

	item = ft_calloc(1, sizeof(t_item));
	if (!item)
		return (NULL);
	init_item(game, window, item, identifier);
	return (item);
}
