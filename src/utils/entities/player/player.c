/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 19:54:55 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	player_looks(t_player *player)
{
	if (player->looking_left)
		player->entity.coords.yaw = ft_normalize_angle(player->entity.coords.yaw - player->key_look_velocity);
	else if (player->looking_right)
		player->entity.coords.yaw = ft_normalize_angle(player->entity.coords.yaw + player->key_look_velocity);
}

static bool	position_overlaps(t_list *entities, t_player *player, t_coords coords)
{
	t_list		*curr;
	t_entity	*curr_entity;

	if (!player->entity.hard)
		return (false);
	curr = entities;
	while (curr)
	{
		curr_entity = curr->data;
        if (curr_entity != (t_entity *)player && curr_entity->hard
            && coords.x + PLAYER_HITBOX_RADIUS >= curr_entity->coords.x
            && coords.x - PLAYER_HITBOX_RADIUS <= (curr_entity->coords.x + curr_entity->size.width)
            && coords.y + PLAYER_HITBOX_RADIUS >= curr_entity->coords.y
            && coords.y - PLAYER_HITBOX_RADIUS <= (curr_entity->coords.y + curr_entity->size.height))
            return (true);
		curr = curr->next;
	}
	return (false);
}

static void	move_player_x(t_list *entities, t_player *player, double angle_radians, double velocity)
{
	double	new_x;

	new_x = player->entity.coords.x + velocity * cos(angle_radians);
	if (!position_overlaps(entities, player, (t_coords){new_x, player->entity.coords.y, 0}))
		player->entity.coords.x = new_x;
}

static void	move_player_y(t_list *entities, t_player *player, double angle_radians, double velocity)
{
	double	new_y;

	new_y = player->entity.coords.y + velocity * sin(angle_radians);
	if (!position_overlaps(entities, player, (t_coords){player->entity.coords.x, new_y, 0}))
		player->entity.coords.y = new_y;
}

static void	player_walk(t_list *entities, t_player *player, double angle)
{
	double	angle_radians;
	double	velocity;

	velocity = player->walk_velocity;
	if (player->sprinting)
		velocity = player->sprint_velocity;
	angle_radians = ft_normalize_angle(angle) * (PI / 180.0);
	move_player_x(entities, player, angle_radians, velocity);
	move_player_y(entities, player, angle_radians, velocity);
}

static void	player_walks(t_list *entities, t_player *player)
{
	if (player->walking_backward)
		player_walk(entities, player, player->entity.coords.yaw - 180.0);
	if (player->walking_right)
		player_walk(entities, player, player->entity.coords.yaw + 90.0);
	if (player->walking_left)
		player_walk(entities, player, player->entity.coords.yaw - 90.0);
	if (player->walking_forward)
		player_walk(entities, player, player->entity.coords.yaw);
}

static void	player_mouse_moviment(t_player *player)
{
	if (!player->mouse_moviment)
		return ;
	player->entity.coords.yaw = ft_normalize_angle(player->entity.coords.yaw + (player->mouse_moviment * player->mouse_look_velocity));
}

static void	player_actions(t_player *player)
{
	if (player->action && player->already_actioned)
		return ;
	player->already_actioned = player->action;
	if (player->action && player->entity.target_entity
		&& player->entity.target_entity->action)
		player->entity.target_entity->action(player->entity.target_entity, (t_entity *)player);
}

static void	player_frame(t_entity *entity)
{
	player_looks((t_player *)entity);
	player_mouse_moviment((t_player *)entity);
	player_walks(cub3d()->game.entities, (t_player *)entity);
	player_actions((t_player *)entity);
}

static void	free_player(void *entity)
{
	free(entity);
}

t_player	*player_new(char direction)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->entity.type = ENTITY_PLAYER;
	player->entity.frame = player_frame;
	player->entity.free = free_player;
	player->entity.hard = true;
	player->key_look_velocity = PLAYER_KEY_LOOK_VELOCITY;
	player->mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY;
	player->walk_velocity = PLAYER_WALK_VELOCITY;
	player->sprint_velocity = PLAYER_SPRINT_VELOCITY;
	if (direction == 'N')
		player->entity.coords.yaw = 270.0;
	else if (direction == 'S')
		player->entity.coords.yaw = 90.0;
	else if (direction == 'W')
		player->entity.coords.yaw = 180.0;
	return (player);
}
