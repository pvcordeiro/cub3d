/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/17 11:59:24 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static t_sprite	*get_door_sprite(t_door *door)
{
    double	current_time;
    double	elapsed_time;
	int		frame_index;

	current_time = ft_get_time();
	elapsed_time = current_time - door->animated_at;
	if (elapsed_time > DOOR_ANIMATION_UPDATE_DELAY * DOOR_ANIMATION_FRAMES)
	{
		door->opening_sprite.index = 0;
		door->closing_sprite.index = 0;
		if (door->opened)
			return (&door->door_opened_sprite);
		return (door->door_sprite);
	}
	frame_index = (int)(elapsed_time / DOOR_ANIMATION_UPDATE_DELAY);
    if (frame_index >= DOOR_ANIMATION_FRAMES)
		frame_index = DOOR_ANIMATION_FRAMES - 1;
	if (door->opened)
	{
		door->opening_sprite.index = frame_index;
		return (&door->opening_sprite);
	}
	door->closing_sprite.index = frame_index;
	return (&door->closing_sprite);
}

static void	set_door_sprite(t_door *door)
{
	if (door->direction == NORTH || door->direction == SOUTH)
	{
		door->base.north_sprite = get_door_sprite(door);
		door->base.south_sprite = get_door_sprite(door);
	}
	else if (door->direction == EAST || door->direction == WEST)
	{
		door->base.east_sprite = get_door_sprite(door);
		door->base.west_sprite = get_door_sprite(door);
	}
}

static void	door_frame(t_entity *entity)
{
	t_door	*door;

	door = (t_door *)entity;
	set_door_sprite(door);
	door->base.base.hard = !door->opened;
}

static void	free_door(void *door)
{
	clear_sprite(&((t_door *)door)->opening_sprite);
	clear_sprite(&((t_door *)door)->door_opened_sprite);
	ft_list_clear_without_free(((t_door *)door)->closing_sprite.images);
	ft_list_destroy(&((t_door *)door)->closing_sprite.images);
	free(door);
}

static void	door_action(t_entity *entity, t_entity *actioner)
{
	(void)actioner;
	((t_door *)entity)->opened = !((t_door *)entity)->opened;
	((t_door *)entity)->animated_at = ft_get_time();
}

static void	*hashmap_get_with_identifier(t_hashmap *hashmap, char identifier, char *rest)
{
	char	*key;
	void	*data;

	key = ft_strf("%c_%s", identifier, rest);
	data = ft_hashmap_get_value(hashmap, key);
	return (free(key), data);
}

static void	init_door_direction_e(t_door *door, t_game *game, char identifier)
{
	char	*direction_str;

	fte_set(ERROR_NO_ERROR);
	direction_str = hashmap_get_with_identifier(game->map->types, identifier, "DIRECTION");
	if (!direction_str)
		return (fte_set(ERROR_DOOR_DIRECTION_MISSING));
	if (ft_strequal(direction_str, "NORTH"))
		door->direction = NORTH;
	else if (ft_strequal(direction_str, "SOUTH"))
		door->direction = SOUTH;
	else if (ft_strequal(direction_str, "EAST"))
		door->direction = EAST;
	else if (ft_strequal(direction_str, "WEST"))
		door->direction = WEST;
	else
		return (fte_set(ERROR_DOOR_DIRECTION_MISSING));
}

static void	init_door_sides(t_door *door, t_game *game, char identifier)
{
	if (door->direction == NORTH || door->direction == SOUTH)
	{
		door->base.west_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SIDES");
		door->base.east_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SIDES");
	}
	else if (door->direction == WEST || door->direction == EAST)
	{
		door->base.north_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SIDES");
		door->base.south_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SIDES");
	}
}

static t_ftm_pitc_config	get_animation_config(t_ftm_image *canvas, int frame)
{
	t_ftm_pitc_config	config;

	ft_bzero(&config, sizeof(t_ftm_pitc_config));
	config.coords = (t_coords){(canvas->size.width / DOOR_ANIMATION_FRAMES) * frame, 0, 0, 0};
	return (config);
}

static void	init_animation_sprites(t_door *door, t_ftm_window *window)
{
	t_ftm_image	*frame;
	t_ftm_image	*door_image;
	int			i;

	door_image = door->door_sprite->images->data;
	init_sprite(&door->opening_sprite, NULL, 0);
	init_sprite(&door->closing_sprite, NULL, 0);
	i = -1;
	while (++i < DOOR_ANIMATION_FRAMES)
	{
		frame = ftm_image_new(window, door_image->size);
		if (!frame)
			return (fte_set(ERROR_INIT_DOOR_FRAME));
		ftm_put_image_to_canvas(frame, door_image, get_animation_config(frame, i));
		ft_list_add(&door->opening_sprite.images, frame, ftm_free_image);
	}
	door->closing_sprite.images = ft_list_clone(door->opening_sprite.images);
	ft_list_reverse(&door->closing_sprite.images);
}

t_door	*door_new_e(char identifier, t_ftm_window *window, t_game *game)
{
	t_door	*door;

	fte_set(ERROR_NO_ERROR);
	door = ft_calloc(1, sizeof(t_door));
	if (!door)
		return (NULL);
	((t_entity *)door)->type = ENTITY_DOOR;
	((t_entity *)door)->frame = door_frame;
	((t_entity *)door)->free = free_door;
	((t_entity *)door)->action = door_action;
	((t_entity *)door)->hard = true;
	((t_entity *)door)->block = true;
	((t_entity *)door)->transparent = true;
	init_sprite(&door->door_opened_sprite, NULL, 0);
	init_door_direction_e(door, game, identifier);
	if (fte_flagged())
		return (free(door), NULL);
	door->door_sprite = hashmap_get_with_identifier(game->sprites, identifier, "DOOR");
	if (!door->door_sprite)
		return (free(door), fte_set(ERROR_DOOR_SPRITE_MISSING), NULL);
	init_door_sides(door, game, identifier);
	init_animation_sprites(door, window);
	return (door);
}
