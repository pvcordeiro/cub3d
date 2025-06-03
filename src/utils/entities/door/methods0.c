/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 01:21:41 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"

void	door_frame(t_entity *entity, double delta_time)
{
	t_door	*door;

	wall_frame(entity, delta_time);
	door = (t_door *)entity;
	door->wall.entity.hard = door->opening_sprite.index != DOOR_ANIMATION_FRAMES - 1;
	door->wall.entity.transparent = door->opening_sprite.index;
	(void)get_sprite_image(&door->opening_sprite);
	if (door->opening_sprite.index == 0 && door->opening_sprite.index != door->last_animation_index)
		fta_play(door->close_sound);
	door->last_animation_index = door->opening_sprite.index;
}

void	clear_door(void *door)
{
	clear_wall(door);
	clear_sprite(&((t_door *)door)->opening_sprite);
}

void	door_action(t_entity *entity, t_entity *actioner)
{
	t_door	*door;

	wall_action(entity, actioner);
	door = (t_door *)entity;
	door->opened = !door->opened;
	door->opening_sprite.reversed = !door->opened;
	door->opening_sprite.running = true;
	door->opening_sprite.updated_at = ft_get_time();
	if (door->opened)
		fta_play(door->open_sound);
}
