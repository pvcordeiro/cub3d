/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_dumb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:34:50 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 13:55:18 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

#define AI_MOVE_INTERVAL 2.0
static void	frame(t_entity *entity, double delta_time)
{
    static double	time_accumulator;
    double			angle_to_player;
    double			dx;
	double			dy;
	double			distance_to_player;

    time_accumulator += delta_time;
    if (cub3d()->game.player)
    {
        dx = cub3d()->game.player->billboard.entity.coords.x - entity->coords.x;
        dy = cub3d()->game.player->billboard.entity.coords.y - entity->coords.y;
        angle_to_player = ft_degrees(atan2(dy, dx));
        entity->coords.yaw = ft_normalize_angle(angle_to_player);
        distance_to_player = sqrt(dx * dx + dy * dy);
        entity->controller.walking_forward = (distance_to_player > 2.0);
        entity->controller.walking_left = false;
        entity->controller.walking_right = false;
        entity->controller.walking_backward = false;
        entity->controller.sprinting = false;
    }
    else if (time_accumulator >= AI_MOVE_INTERVAL)
    {
        entity->controller.walking_forward = rand() % 2;
        entity->controller.walking_left = rand() % 2;
        entity->controller.walking_backward = rand() % 2;
        entity->controller.walking_right = rand() % 2;
        entity->controller.sprinting = rand() % 2;
        time_accumulator = 0.0;
    }
    moviment_frame(entity, delta_time);
}

void	init_ai_dumb_controller(t_entity *entity)
{
	entity->controller.frame = frame;
	entity->controller.key_look_velocity = PLAYER_KEY_LOOK_VELOCITY / 2;
	entity->controller.mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY / 2;
	entity->controller.walk_velocity = PLAYER_WALK_VELOCITY / 2;
	entity->controller.sprint_velocity = PLAYER_SPRINT_VELOCITY / 2;
}
