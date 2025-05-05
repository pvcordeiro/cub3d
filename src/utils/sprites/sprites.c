/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:01:44 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/05 01:10:47 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_sprite(t_sprite *sprite, t_list *images, t_time update_delay)
{
	sprite->images = images;
	sprite->update_delay = update_delay;
	sprite->updated_at = ft_get_time();
}

void	destroy_master_sprites(t_master_sprites *master_sprites)
{
	ft_list_destroy(&master_sprites->missing.images);
}

static t_list	*get_missing_images_e(void)
{
	t_list	*list;
	t_image	*image;

	ft_error(ERROR_NO_ERROR);
	list = NULL;
	image = image_from_file(MISSING_IMAGE_PATH);
	if (!image)
		return (ft_error(ERROR_MISSING_TEXTURE_LOAD), NULL);
	ft_list_add(&list, image, (void (*)(void *))free_image);
	return (list);
}

void	load_missing_e(t_sprite *sprite, t_list	*(*get_images_list_e)(void))
{
	t_list	*images;

	images = get_images_list_e();
	if (ft_has_error())
		return ;
	init_sprite(sprite, images, 0);
}

void	load_master_sprites(t_master_sprites *master_sprites, t_hashmap *types)
{
	(void)types;
	master_sprites->initialized = false;
	load_missing_e(&master_sprites->missing, get_missing_images_e);
	master_sprites->initialized = true;
}

t_image	*get_sprite_image(t_sprite *sprite)
{
	t_list	*curr_image_node;

	if (!sprite->images)
	{
		if (sprite != &cub3d()->master_sprites.missing)
			return (get_sprite_image(&cub3d()->master_sprites.missing));
		return (NULL);
	}
	curr_image_node = ft_list_index(sprite->images, sprite->index);
	if (!curr_image_node)
		return (NULL);
	if (ft_get_time() - sprite->updated_at > sprite->update_delay)
	{
		sprite->index++;
		if (sprite->index >= ft_list_size(sprite->images))
			sprite->index = 0;
		sprite->updated_at = ft_get_time();
	}
	return (sprite->images->data);
}
