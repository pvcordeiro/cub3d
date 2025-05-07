/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:20:04 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:15:58 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_sprites_e(t_window *window, t_game *game)
{
	t_sprite	*sprite;
	t_ftm_image		*image;
	t_list		*image_list;
	t_element	*element;

	ft_error(ERROR_NO_ERROR);
	game->sprites = ft_hashmap_new();
	if (!game->sprites)
		return (ft_error(ERROR_INIT_SPRITES));
	element = *game->map->types->table;
	while (element)
	{
		if (!ft_str_endswith(element->value, ".xpm") || !ft_is_file(element->value))
		{
			element = element->next;
			continue ;
		}
		image = ftm_image_from_file(window, element->value);
		if (!image)
			return (ft_hashmap_destroy(game->sprites), ft_error(ERROR_LOAD_SPRITE));
		if (ft_hashmap_get_value(game->sprites, element->key))
		{
			image_list = ((t_sprite *)ft_hashmap_get_value(game->sprites, element->key))->images;
			ft_list_add(&image_list, image, ftm_free_image);
		}
		else
		{
			sprite = sprite_new(ft_list_new(image, ftm_free_image), 0);
			if (!sprite)
				return (ft_hashmap_destroy(game->sprites), ft_error(ERROR_LOAD_SPRITE));
			ft_hashmap_set(game->sprites, element->key, sprite, free_sprite);
		}
		element = element->next;
	}
}
