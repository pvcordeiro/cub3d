/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/28 20:01:27 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	play_close_sound(t_door *door)
{
	(void)get_sprite_image(&door->opening_sprite);
	if (door->opening_sprite.index == 0 && door->opening_sprite.index != door->last_animation_index)
		fta_play(door->close_sound);
	door->last_animation_index = door->opening_sprite.index;
}

static void	door_frame(t_entity *entity, double delta_time)
{
	t_door	*door;

	(void)delta_time;
	door = (t_door *)entity;
	door->wall.entity.hard = door->opening_sprite.index != DOOR_ANIMATION_FRAMES - 1;
	door->wall.entity.transparent = door->opening_sprite.index;
	play_close_sound(door);
}

static void	free_door(void *door)
{
	clear_sprite(&((t_door *)door)->opening_sprite);
	free(door);
}

static void	update_door_animation(t_door *door)
{
	door->opening_sprite.reversed = !door->opened;
	door->opening_sprite.running = true;
	door->opening_sprite.updated_at = ft_get_time();
}

static void	door_action(t_entity *entity, t_entity *actioner)
{
	t_door	*door;

	(void)actioner;
	door = (t_door *)entity;
	door->opened = !door->opened;
	update_door_animation(door);
	if (door->opened)
		fta_play(door->open_sound);
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
		door->wall.west_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SIDES");
		door->wall.east_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SIDES");
	}
	else if (door->direction == WEST || door->direction == EAST)
	{
		door->wall.north_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SIDES");
		door->wall.south_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SIDES");
	}
}

static t_ftm_pitc_config	get_animation_config(t_ftm_image *frame, int i)
{
	t_ftm_pitc_config	config;

	ft_bzero(&config, sizeof(t_ftm_pitc_config));
	config.coords = (t_coords){(frame->size.width / DOOR_ANIMATION_FRAMES) * i, 0, 0};
	return (config);
}

static void	init_animation_sprites_e(t_door *door, t_ftm_window *window)
{
	t_ftm_image	*frame;
	t_ftm_image	*door_image;
	int			i;

	fte_set(ERROR_NO_ERROR);
	door_image = door->door_sprite->images->data;
	init_sprite(&door->opening_sprite, NULL, DOOR_ANIMATION_DURATION);
	i = -1;
	while (++i < DOOR_ANIMATION_FRAMES - 1)
	{
		frame = ftm_image_new(window, door_image->size);
		if (!frame)
			return (fte_set(ERROR_INIT_DOOR_FRAME));
		ftm_put_image_to_canvas(frame, door_image, get_animation_config(frame, i));
		ft_list_add(&door->opening_sprite.images, frame, ftm_free_image);
	}
	ft_list_add(&door->opening_sprite.images, NULL, NULL);
}

static void	init_sounds(char identifier, t_door *door, t_game *game)
{
	door->open_sound = hashmap_get_with_identifier(game->sounds, identifier, "OPEN");
	door->close_sound = hashmap_get_with_identifier(game->sounds, identifier, "CLOSE");
}

static void	set_sprites(t_door *door)
{
	if (door->direction == NORTH || door->direction == SOUTH)
	{
		door->wall.north_sprite = &door->opening_sprite;
		door->wall.south_sprite = &door->opening_sprite;
	}
	else if (door->direction == EAST || door->direction == WEST)
	{
		door->wall.east_sprite = &door->opening_sprite;
		door->wall.west_sprite = &door->opening_sprite;
	}
}

void	init_door_e(t_game *game, t_door *door, char identifier, t_ftm_window *window)
{
	fte_set(ERROR_NO_ERROR);
	init_wall(game, &door->wall, identifier);
	door->wall.entity.type = ENTITY_DOOR;
	door->wall.entity.frame = door_frame;
	door->wall.entity.free = free_door;
	door->wall.entity.action = door_action;
	init_door_direction_e(door, game, identifier);
	if (fte_flagged())
		return ;
	door->door_sprite = hashmap_get_with_identifier(game->sprites, identifier, "DOOR_SPRITE");
	if (!door->door_sprite)
		return (fte_set(ERROR_DOOR_SPRITE_MISSING));
	init_door_sides(door, game, identifier);
	init_animation_sprites_e(door, window);
	if (fte_flagged())
		return ;
	init_sounds(identifier, door, game);
	set_sprites(door);
}

t_door	*door_new_e(t_game *game, t_ftm_window *window, char identifier)
{
	t_door	*door;

	fte_set(ERROR_NO_ERROR);
	door = ft_calloc(1, sizeof(t_door));
	if (!door)
		return (NULL);
	init_door_e(game, door, identifier, window);
	if (fte_flagged())
		return (free(door), NULL);
	return (door);
}
