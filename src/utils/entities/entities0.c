/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:49:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 03:22:31 by afpachec         ###   ########.fr       */
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

void	call_entity_frames(t_game *game, t_fps *fps)
{
	t_list		*curr;
	t_entity	*entity;

	curr = game->entities;
	while (curr)
	{
		entity = curr->data;
		entity->frame(game, entity, fps->delta_time);
		curr = curr->next;
	}
}

void	call_entity_keys(t_game *game, t_ftm_key_hook_values kvh)
{
	t_list		*curr;
	t_entity	*entity;

	curr = game->entities;
	while (curr)
	{
		entity = curr->data;
		if (entity->active && entity->controller.key)
			entity->controller.key(game, entity, kvh);
		curr = curr->next;
	}
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

void	free_entity(void *data)
{
	if (!data)
		return ;
	((t_entity *)data)->clear(data);
	free(data);
}

bool	add_item_to_inventory(t_character *character, t_item *item)
{
	int	i;

	if (!character || !item)
		return (false);
	i = -1;
	while (++i < INVENTORY_SIZE)
	{
		if (character->inventory[i])
			continue ;
		character->inventory[i] = item;
		return (true);
	}
	return (false);
}

void	clear_3d_sprite(t_sprite **sprites)
{
	int	i;

	if (!sprites)
		return ;
	i = -1;
	while (++i < 360)
	{
		if (!sprites[i])
			continue ;
		free(sprites[i]);
		sprites[i] = NULL;
	}
}

void	fill_3d_sprites_from_src(t_sprite **dst, t_sprite **src)
{
	int	i;

	i = -1;
	clear_3d_sprite(dst);
	while (++i < 360)
		sprite_soft_copy(&(dst[i]), src[i]);
}

void	fill_3d_sprites_from_single(t_sprite **dst, t_sprite *src)
{
	int	i;

	i = -1;
	clear_3d_sprite(dst);
	while (++i < 360)
		sprite_soft_copy(&(dst[i]), src);
}

void	fill_3d_sprites_from_game(t_game *game, t_sprite **dst, char identifier, char *key)
{
    t_sprite	**sprites;
    t_sprite	*sprite;

    sprites = hashmap_get_with_identifier(game, game->sprites_3d, identifier, key);
    if (sprites)
        return (fill_3d_sprites_from_src(dst, sprites));
    sprite = hashmap_get_with_identifier(game, game->sprites, identifier, key);
    fill_3d_sprites_from_single(dst, sprite);
}

void	reset_3d_sprites(t_sprite **sprites)
{
	int	i;

	if (!sprites)
		return ;
	i = -1;
	while (++i < 360)
	{
		if (!sprites[i])
			continue ;
		sprites[i]->index = 0;
		sprites[i]->updated_at = ft_get_time();
		sprites[i]->running = true;
		sprites[i]->reversed = false;
	}
}
