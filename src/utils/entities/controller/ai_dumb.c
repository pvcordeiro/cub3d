/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_dumb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:34:50 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/01 18:56:08 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

#define AI_MOVE_INTERVAL 2.0

static void	frame(t_entity *entity, double delta_time)
{
	static double time_accumulator = 0.0;
	t_controller *c = &entity->controller;

	time_accumulator += delta_time;

	if (time_accumulator >= AI_MOVE_INTERVAL)
	{
		c->walking_forward = rand() % 2;
		c->walking_left = rand() % 2;
		c->walking_backward = rand() % 2;
		c->walking_right = rand() % 2;
		c->sprinting = rand() % 2;
		time_accumulator = 0.0;
	}
	moviment_frame(entity, delta_time);
}

void	init_ai_dumb_controller(t_entity *entity)
{
	entity->controller.frame = frame;
	entity->controller.key_look_velocity = PLAYER_KEY_LOOK_VELOCITY;
	entity->controller.mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY;
	entity->controller.walk_velocity = PLAYER_WALK_VELOCITY;
	entity->controller.sprint_velocity = PLAYER_SPRINT_VELOCITY;
}
