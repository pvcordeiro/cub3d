/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/28 20:02:10 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	player_looks(t_player *player, double delta_time)
{
	double	velocity;

	velocity = player->key_look_velocity * delta_time;
	if (player->looking_left)
		player->billboard.entity.coords.yaw = ft_normalize_angle(player->billboard.entity.coords.yaw - velocity);
	else if (player->looking_right)
		player->billboard.entity.coords.yaw = ft_normalize_angle(player->billboard.entity.coords.yaw + velocity);
}

static bool	position_overlaps(t_list *entities, t_player *player, t_coords coords)
{
	t_list		*curr;
	t_entity	*curr_entity;

	if (!player->billboard.entity.hard)
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
		{
			fta_play(player->collision_sound);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

static void	move_player_x(t_list *entities, t_player *player, double angle, double velocity)
{
	double	new_x;

	new_x = player->billboard.entity.coords.x + velocity * ft_cos_degrees(angle);
	if (!position_overlaps(entities, player, (t_coords){new_x, player->billboard.entity.coords.y, 0}))
		player->billboard.entity.coords.x = new_x;
}

static void	move_player_y(t_list *entities, t_player *player, double angle, double velocity)
{
	double	new_y;

	new_y = player->billboard.entity.coords.y + velocity * ft_sin_degrees(angle);
	if (!position_overlaps(entities, player, (t_coords){player->billboard.entity.coords.x, new_y, 0}))
		player->billboard.entity.coords.y = new_y;
}

static void	player_walk(t_list *entities, t_player *player, double angle, double delta_time)
{
	double	velocity;

	velocity = player->walk_velocity;
	if (player->sprinting)
		velocity = player->sprint_velocity;
	velocity *= delta_time;
	move_player_x(entities, player, angle, velocity);
	move_player_y(entities, player, angle, velocity);
}

static void	player_walks(t_list *entities, t_player *player, double delta_time)
{
	if (player->walking_backward)
		player_walk(entities, player, player->billboard.entity.coords.yaw - 180.0, delta_time);
	if (player->walking_right)
		player_walk(entities, player, player->billboard.entity.coords.yaw + 90.0, delta_time);
	if (player->walking_left)
		player_walk(entities, player, player->billboard.entity.coords.yaw - 90.0, delta_time);
	if (player->walking_forward)
		player_walk(entities, player, player->billboard.entity.coords.yaw, delta_time);
}

static void	player_mouse_moviment(t_player *player, double delta_time)
{
	double	velocity;

	if (!player->mouse_moviment)
		return ;
	velocity = (player->mouse_moviment * player->mouse_look_velocity) * delta_time;
	player->billboard.entity.coords.yaw = ft_normalize_angle(player->billboard.entity.coords.yaw + velocity);
}

static void	player_actions(t_player *player)
{
	if (player->action && player->already_actioned)
		return ;
	player->already_actioned = player->action;
	if (player->action && player->billboard.entity.target_entity
		&& player->billboard.entity.target_entity->action)
		player->billboard.entity.target_entity->action(player->billboard.entity.target_entity, (t_entity *)player);
}

static void	player_frame(t_entity *entity, double delta_time)
{
	player_looks((t_player *)entity, delta_time);
	player_mouse_moviment((t_player *)entity, delta_time);
	player_walks(cub3d()->game.entities, (t_player *)entity, delta_time);
	player_actions((t_player *)entity);
}

static void	free_player(void *entity)
{
	free(entity);
}

static void	init_sounds(t_player *player, t_game *game)
{
	player->collision_sound = ft_hashmap_get_value(game->sounds, "COLLISION");
}

t_player	*player_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_player	*player;

	(void)window;
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->billboard.entity.type = ENTITY_PLAYER;
	player->billboard.entity.frame = player_frame;
	player->billboard.entity.free = free_player;
	player->billboard.entity.hard = true;
	player->billboard.entity.identifier = identifier;
	player->billboard.entity.max_health = 100;
	player->billboard.entity.health = player->billboard.entity.max_health;
	player->key_look_velocity = PLAYER_KEY_LOOK_VELOCITY;
	player->mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY;
	player->walk_velocity = PLAYER_WALK_VELOCITY;
	player->sprint_velocity = PLAYER_SPRINT_VELOCITY;
	init_sounds(player, game);
	if (identifier == 'N')
		player->billboard.entity.coords.yaw = 270.0;
	else if (identifier == 'S')
		player->billboard.entity.coords.yaw = 90.0;
	else if (identifier == 'W')
		player->billboard.entity.coords.yaw = 180.0;
	return (player);
}
