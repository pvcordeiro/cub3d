/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:49:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/27 19:55:50 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static t_sprite	*get_wall_sprite(t_wall *wall, t_direction direction)
{
	if (direction == NORTH)
		return (wall->north_sprite);
	else if (direction == SOUTH)
		return (wall->south_sprite);
	else if (direction == WEST)
		return (wall->west_sprite);
	else if (direction == EAST)
		return (wall->east_sprite);
	return (NULL);
}

t_sprite	*get_entity_sprite(t_entity *entity, t_direction direction)
{
	if (!entity)
		return (NULL);
	if (entity->type == ENTITY_WALL || entity->type == ENTITY_DOOR)
		return (get_wall_sprite((t_wall *)entity, direction));
	return (NULL);
}

void	call_entity_frames(t_list *entities, t_fps *fps)
{
	t_list		*curr;
	t_entity	*entity;

	curr = entities;
	while (curr)
	{
		entity = curr->data;
		entity->frame(entity, fps->delta_time);
		curr = curr->next;
	}
}

void	*hashmap_get_with_identifier(t_hashmap *hashmap, char identifier, char *rest)
{
	char	*key;
	void	*data;

	key = ft_strdup(rest);
	if (identifier != '1')
		key = (free(key), ft_strf("%c_%s", identifier, rest));
	data = ft_hashmap_get_value(hashmap, key);
	return (free(key), data);
}

bool	entity_x_is_transparent(t_entity *entity, t_direction direction, double x)
{t_ftm_image		*image;
	unsigned int	*pixel;
	double			actual_x;

	actual_x = x;
	if (direction == NORTH || direction == EAST)
		actual_x = 1.0 - x;
	image = get_sprite_image(get_entity_sprite(entity, direction));
	if (!image)
		return (true);
	pixel = ftm_image_pixel(image, (t_coords){actual_x * image->size.width, image->size.height / 2, 0});
	if (!pixel)
		return (true);
	return (!(*pixel >> 24));
}
