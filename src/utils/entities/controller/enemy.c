/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:10:29 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/16 00:30:53 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static void	frame(t_entity *entity, double delta_time)
{
	t_character	*character;

	moviment_frame(entity, delta_time);
	if (!entity->character)
		return ;
	character = (t_character *)entity;
	targets_frame(character);
	if (!character->target_entity)
		return ;
	entity->coords.yaw = entity->coords.yaw
		+ ft_angle_distance(entity->coords,
			character->target_entity->coords);
}

void	init_enemy_controller(t_entity *entity)
{
	entity->controller.frame = frame;
	entity->controller.key_look_velocity = PLAYER_KEY_LOOK_VELOCITY / 1.5;
	entity->controller.mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY / 1.5;
	entity->controller.walk_velocity = PLAYER_WALK_VELOCITY / 1.5;
	entity->controller.sprint_velocity = PLAYER_SPRINT_VELOCITY / 1.5;
}
