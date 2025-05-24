/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:20:04 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/23 22:56:06 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_sprites_e(t_ftm_window *window, t_game *game)
{
	t_sprite	*sprite;
	t_ftm_image	*image;
	t_element	*el;
	char		*path;

	fte_set(ERROR_NO_ERROR);
	image = NULL;
	el = *game->map->types->table;
	image = NULL;
	while (el)
	{
		if (((char *)el->value)[0] == '*')
			path = ft_strdup(el->value + 1);
		else
			path = ft_strdup(el->value);
		if (ft_strequal(path, "NULL") || (ft_str_endswith(path, ".xpm") && ft_is_file(path)))
		{
			if (!ft_strequal(path, "NULL"))
			{
				image = ftm_image_from_file(window, path, ((char *)el->value)[0] == '*');
				if (!image)
					return (free(path), fte_set(ERROR_LOAD_SPRITE));
			}
			if (!ft_hashmap_get_value(game->sprites, el->key))
			{
				sprite = sprite_new(NULL, 0);
				if (!sprite)
					return (free(path), fte_set(ERROR_LOAD_SPRITE));
				ft_hashmap_set(game->sprites, el->key, sprite, free_sprite);
			}
			if (!ft_strequal(path, "NULL"))
				ft_list_add(&((t_sprite *)ft_hashmap_get_value(game->sprites,
							el->key))->images, image, ftm_free_image);
		}
		free(path);
		el = el->next;
	}
}
