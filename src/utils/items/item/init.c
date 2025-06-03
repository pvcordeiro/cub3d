/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 21:20:05 by afpachec         ###   ########.fr       */
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
	item->identifier = identifier;
	item->name = hashmap_get_with_identifier(game->map->types, identifier,
		"NAME");
	item->description = hashmap_get_with_identifier(game->map->types,
		identifier, "DESCRIPTION");
	item->icon_sprite = hashmap_get_with_identifier(game->sprites,
		identifier, "ICON_SPRITE");
	item->screen_sprite = hashmap_get_with_identifier(game->sprites,
		identifier, "SCREEN_SPRITE");
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
