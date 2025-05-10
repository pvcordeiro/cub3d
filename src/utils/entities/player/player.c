/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/10 11:26:55 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	player_looks(t_player *player)
{
	if (player->looking_left)
		player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw - player->key_look_velocity);
	else if (player->looking_right)
		player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw + player->key_look_velocity);
}

static bool	position_overlaps(t_list *entities, t_player *player, t_coords coords)
{
	t_list		*curr;
	t_entity	*curr_entity;

	curr = entities;
	while (curr)
	{
		curr_entity = curr->data;
        if (curr_entity != (t_entity *)player && curr_entity->hard
            && (int)(coords.x + PLAYER_HITBOX_RADIUS) >= (int)curr_entity->coords.x
            && (int)(coords.x - PLAYER_HITBOX_RADIUS) <= (int)(curr_entity->coords.x + 0.9)
            && (int)(coords.y + PLAYER_HITBOX_RADIUS) >= (int)curr_entity->coords.y
            && (int)(coords.y - PLAYER_HITBOX_RADIUS) <= (int)(curr_entity->coords.y + 0.9))
            return (true);
		curr = curr->next;
	}
	return (false);
}

static void	move_player_x(t_list *entities, t_player *player, double angle_radians, double velocity)
{
	double	new_x;

	new_x = player->base.coords.x + velocity * cos(angle_radians);
	if (!position_overlaps(entities, player, (t_coords){new_x, player->base.coords.y, 0, 0}))
		player->base.coords.x = new_x;
}

static void	move_player_y(t_list *entities, t_player *player, double angle_radians, double velocity)
{
	double	new_y;

	new_y = player->base.coords.y + velocity * sin(angle_radians);
	if (!position_overlaps(entities, player, (t_coords){player->base.coords.x, new_y, 0, 0}))
		player->base.coords.y = new_y;
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
		player_walk(entities, player, player->base.coords.yaw - 180.0);
	if (player->walking_right)
		player_walk(entities, player, player->base.coords.yaw + 90.0);
	if (player->walking_left)
		player_walk(entities, player, player->base.coords.yaw - 90.0);
	if (player->walking_forward)
		player_walk(entities, player, player->base.coords.yaw);
}

static void	player_rays(t_game *game, t_player *player)
{
	t_coords	ray_coords;
	t_raycast	raycast;
	size_t		i;
	double		angle;

	i = -1;
	angle = player->base.coords.yaw - PLAYER_FOV / 2;
	ray_coords = player->base.coords;
	while (++i < PLAYER_RAYS)
	{
		ray_coords.yaw = ft_normalize_angle(angle + ((PLAYER_FOV / PLAYER_RAYS)
					* i));
		raycast = send_ray(game, ray_coords);
		player->rays[i].direction_of_hit_on_entity = raycast.direction_of_hit_on_entity;
		player->rays[i].length = raycast.length;
		player->rays[i].hit_entity = raycast.hit_entity;
		player->rays[i].x_of_hit_in_entity = raycast.x_of_hit_in_entity;
		player->rays[i].angle = ray_coords.yaw;
	}
}

static void	player_frame(t_entity *entity)
{
	player_looks((t_player *)entity);
	player_walks(cub3d()->game.entities, (t_player *)entity);
	player_rays(&cub3d()->game, (t_player *)entity);
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
	player->base.type = ENTITY_PLAYER;
	player->base.frame = player_frame;
	player->base.free = free_player;
	player->key_look_velocity = PLAYER_KEY_LOOK_VELOCITY;
	player->mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY;
	player->using_mouse = true;
	player->walk_velocity = PLAyER_WALK_VELOCITY;
	player->sprint_velocity = PLAYER_SPRINT_VELOCITY;
	if (direction == 'W')
		player->base.coords.yaw = 180.0;
	else if (direction == 'S')
		player->base.coords.yaw = 0.0;
	else if (direction == 'N')
		player->base.coords.yaw = 270.0;
	else if (direction == 'E')
		player->base.coords.yaw = 90.0;
	return (player);
}
