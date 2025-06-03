/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:35:54 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 01:20:35 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static void	frame(t_entity *entity, double delta_time)
{
	moviment_frame(entity, delta_time);
}

static void	key(t_entity *entity, int key, bool down)
{
	if (key == XK_w)
		entity->controller.walking_forward = down;
	if (key == XK_a)
		entity->controller.walking_left = down;
	if (key == XK_s)
		entity->controller.walking_backward = down;
	if (key == XK_d)
		entity->controller.walking_right = down;
	if (key == XK_Right)
		entity->controller.looking_right = down;
	if (key == XK_Left)
		entity->controller.looking_left = down;
	if (key == XK_space)
		entity->controller.action = down;
	if (key == XK_Shift_L || key == XK_Shift_R)
		entity->controller.sprinting = down;
}

void	init_player_controller(t_entity *entity)
{
	entity->controller.frame = frame;
	entity->controller.key_look_velocity = PLAYER_KEY_LOOK_VELOCITY;
	entity->controller.mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY;
	entity->controller.walk_velocity = PLAYER_WALK_VELOCITY;
	entity->controller.sprint_velocity = PLAYER_SPRINT_VELOCITY;
	entity->controller.key = key;
}
