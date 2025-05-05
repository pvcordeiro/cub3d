/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:01:44 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/05 22:28:03 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

void	destroy_master_sprites(t_master_sprites *master_sprites)
{
	ft_list_destroy(&master_sprites->missing.images);
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
	if (ft_get_time() - sprite->updated_at > sprite->update_delay)
	{
		sprite->index++;
		if (sprite->index >= ft_list_size(sprite->images))
			sprite->index = 0;
		sprite->updated_at = ft_get_time();
	}
	curr_image_node = ft_list_index(sprite->images, sprite->index);
	if (!curr_image_node)
		return (NULL);
	return (curr_image_node->data);
}

void	free_sprite(void *data)
{
	ft_list_destroy(&((t_sprite *)data)->images);
	free(data);
}
