/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvcordeiro <pvcordeiro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:20:04 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/14 16:41:29 by pvcordeiro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_sprites_e(t_ftm_window *window, t_game *game)
{
	t_sprite	*sprite;
	t_ftm_image	*image;
	t_element	*el;

	fte_set(ERROR_NO_ERROR);
	el = *game->map->types->table;
	image = NULL;
	while (el)
	{
		if (ft_strequal(el->value, "NULL") || (ft_str_endswith(el->value,
					".xpm") && ft_is_file(el->value)))
		{
			if (!ft_strequal(el->value, "NULL"))
			{
				image = ftm_image_from_file(window, el->value);
				if (!image)
					return (fte_set(ERROR_LOAD_SPRITE));
			}
			if (!ft_hashmap_get_value(game->sprites, el->key))
			{
				sprite = sprite_new(NULL, 0);
				if (!sprite)
					return (fte_set(ERROR_LOAD_SPRITE));
				ft_hashmap_set(game->sprites, el->key, sprite, free_sprite);
			}
			if (!ft_strequal(el->value, "NULL"))
				ft_list_add(&((t_sprite *)ft_hashmap_get_value(game->sprites,
							el->key))->images, image, ftm_free_image);
		}
		el = el->next;
	}
}
