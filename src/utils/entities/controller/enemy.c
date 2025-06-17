/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:10:29 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/17 14:54:06 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

#define SAFE_DISTANCE 2.0
#define STRAFE_INTERVAL 1.0
#define FIRE_CHANCE 0.05
#define LOOK_AROUND_CHANCE 0.1

static void	look_at_target(t_entity *entity, t_entity *target_entity)
{
	double	angle;

	angle = ft_angle_distance(entity->coords, target_entity->coords);
	entity->controller.prev_target = target_entity;
	entity->controller.last_seen_target = ft_get_time(); 
	entity->controller.last_target_position = target_entity->coords;
	if (angle >= 180)
		entity->coords.yaw -= angle;
	else
		entity->coords.yaw += angle;
	entity->controller.prev_angle = entity->coords.yaw;
}

static void	update_movement(t_entity *entity, t_entity *target_entity, double delta_time)
{
	double	dist;

	dist = ft_distance(entity->coords, target_entity->coords);
	if (dist > SAFE_DISTANCE + 1.5)
	{
		entity->controller.sprinting = true;
		entity->controller.walking_forward = true;
	}
	else if (dist < SAFE_DISTANCE - 1.5)
		entity->controller.walking_backward = true;
	entity->controller.time_accumulator += delta_time;
	if (entity->controller.time_accumulator > STRAFE_INTERVAL)
	{
		entity->controller.time_accumulator = 0.0;
		int strafe = rand() % 3;
		if (strafe == 0)
			entity->controller.walking_left = true;
		else if (strafe == 1)
			entity->controller.walking_right = true;
	}
}

static void	remove_attributes(t_character *character, t_controller *controller)
{
	controller->walking_forward = false;
	controller->walking_backward = false;
	controller->walking_left = false;
	controller->walking_right = false;
	controller->sprinting = false;
	controller->looking_left = false;
	controller->looking_right = false;
	if (character->inventory[character->inventory_index]
		&& ft_get_time() - character->inventory[character->inventory_index]->last_use >= character->inventory[character->inventory_index]->screen_use_sprite->update_delay * 2) 
		character->inventory[character->inventory_index]->user = NULL;
	character->target_entity = NULL;
}

static void	look_around(t_character *character, t_controller *controller)
{
	controller->walking_forward = false;
	if (ft_get_time() - controller->last_seen_target < 10000)
	{
		controller->walking_forward = true;
		if (ft_get_time() - controller->last_seen_target < 5000
			&& controller->prev_target)
		{
			character->billboard.entity.coords.yaw += ft_angle_distance(
				character->billboard.entity.coords,
				controller->last_target_position);
			return ;
		}
		character->billboard.entity.coords.yaw += ft_angle_distance(
			character->billboard.entity.coords,
			controller->prev_target->coords);
		return ;
	}
    if ((double)rand() / RAND_MAX < LOOK_AROUND_CHANCE)
    {
		controller->moving_to_angle = ft_normalize_angle(controller->prev_angle + 90.0);
        if (ft_angle_distance(character->billboard.entity.coords, (t_coords){0, 0, controller->moving_to_angle}) > 180)
            controller->moving_to_angle = ft_normalize_angle(controller->prev_angle - 90.0);
    }
	if (controller->moving_to_angle == character->billboard.entity.coords.yaw)
		return ;
	if (ft_angle_distance(character->billboard.entity.coords, (t_coords){0, 0, controller->moving_to_angle}) > 180)
		controller->looking_left = true;
	else
		controller->looking_right = true;
}

static void	frame(t_entity *entity, double delta_time)
{
	t_character	*character;

	if (!entity->character)
		return ;
	character = (t_character *)entity;
	remove_attributes(character, &entity->controller);
	if (character->dead)
		return ;
	targets_frame(character, 120);
	if (!character->target_entity || character->target_entity->type != ENTITY_PLAYER
		|| ((t_character *)character->target_entity)->dead)
		look_around(character, &entity->controller);
	else
	{
		look_at_target(entity, character->target_entity);
		if (character->inventory[character->inventory_index]
			&& (double)rand() / RAND_MAX < FIRE_CHANCE)
			character->inventory[character->inventory_index]->user = character;
		else if (!character->inventory[character->inventory_index] || !character->inventory[character->inventory_index]->user)
			update_movement(entity, character->target_entity, delta_time);
	}
	moviment_frame(entity, delta_time);
}

void	init_enemy_controller(t_entity *entity)
{
	entity->controller.frame = frame;
	entity->controller.prev_angle = entity->coords.yaw;
	entity->controller.key_look_velocity = PLAYER_KEY_LOOK_VELOCITY / 1.5;
	entity->controller.mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY / 1.5;
	entity->controller.walk_velocity = PLAYER_WALK_VELOCITY / 1.5;
	entity->controller.sprint_velocity = PLAYER_SPRINT_VELOCITY / 1.5;
}
