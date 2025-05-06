/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:32:44 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/05 22:32:37 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

static void	init_sprite(t_sprite *sprite, t_list *images, t_time update_delay)
{
	sprite->images = images;
	sprite->update_delay = update_delay;
	sprite->updated_at = ft_get_time();
}

t_sprite	*sprite_new(t_list *images, t_time update_delay)
{
	t_sprite	*sprite;

	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	init_sprite(sprite, images, update_delay);
	return (sprite);
}

static void	load_sprite_e(t_sprite *sprite, t_list	*(*get_images_list)(void))
{
	t_list	*images;

	ft_error(ERROR_NO_ERROR);
	images = get_images_list();
	if (!images)
		return (ft_error(ERROR_LOAD_SPRITE));
	init_sprite(sprite, images, 0);
}

static void	load_from_types_e(t_master_sprites *master_sprites, t_hashmap *types)
{
	t_sprite	*sprite;
	t_image		*image;
	t_list		*image_list;
	t_element	*element;

	ft_error(ERROR_NO_ERROR);
	element = *types->table;
	while (element)
	{
		if (!ft_str_endswith(element->value, ".xpm") || !ft_is_file(element->value))
		{
			element = element->next;
			continue ;
		}
		image = image_from_file(element->value);
		if (!image)
			return (ft_hashmap_destroy(master_sprites->sprites), ft_error(ERROR_LOAD_SPRITE));
		if (ft_hashmap_get_value(master_sprites->sprites, element->key))
		{
			image_list = ((t_sprite *)ft_hashmap_get_value(master_sprites->sprites, element->key))->images;
			ft_list_add(&image_list, image, free_image);
		}
		else
		{
			sprite = sprite_new(ft_list_new(image, free_image), 0);
			if (!sprite)
				return (ft_hashmap_destroy(master_sprites->sprites), ft_error(ERROR_LOAD_SPRITE));
			ft_hashmap_set(master_sprites->sprites, element->key, sprite, free_sprite);
		}
		element = element->next;
	}
}

void	load_master_sprites_e(t_master_sprites *master_sprites, t_hashmap *types)
{
	(void)types;
	master_sprites->initialized = false;
	load_sprite_e(&master_sprites->missing, get_missing_images);
	if (ft_has_error())
		return ;
	master_sprites->sprites = ft_hashmap_new();
	if (!master_sprites->sprites)
		return (ft_list_destroy(&master_sprites->missing.images), ft_error(ERROR_INIT_SPRITES));
	load_from_types_e(master_sprites, types);
	if (ft_has_error())
		return (ft_list_destroy(&master_sprites->missing.images));
	master_sprites->initialized = true;
}
