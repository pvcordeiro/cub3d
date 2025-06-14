/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvcordeiro <pvcordeiro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/14 15:12:06 by pvcordeiro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	player_looks(t_player *player, double delta_time)
{
	double	look_velocity;

	look_velocity = player->key_look_velocity * delta_time;
	if (player->looking_left)
		player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw
				- player->key_look_velocity - look_velocity);
	else if (player->looking_right)
		player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw
				+ player->key_look_velocity + look_velocity);
}

static void	player_walk(t_player *player, double angle,
		double delta_time)
{
	double	angle_radians;
	double	velocity;

	velocity = player->walk_velocity;
	velocity *= delta_time;
	angle_radians = ft_normalize_angle(angle) * (PI / 180.0);
	player->base.coords.x = player->base.coords.x + velocity * cos(angle_radians);
	player->base.coords.y = player->base.coords.y + velocity * sin(angle_radians);
}

static void	player_walks(t_player *player, double delta_time)
{
	if (player->walking_backward)
		player_walk(player, player->base.coords.yaw - 180.0,
			delta_time);
	if (player->walking_right)
		player_walk(player, player->base.coords.yaw + 90.0,
			delta_time);
	if (player->walking_left)
		player_walk(player, player->base.coords.yaw - 90.0,
			delta_time);
	if (player->walking_forward)
		player_walk(player, player->base.coords.yaw, delta_time);
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

static void	player_frame(t_entity *entity, double delta_time)
{
	player_looks((t_player *)entity, delta_time);
	player_walks((t_player *)entity, delta_time);
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
	player->walk_velocity = PLAYER_WALK_VELOCITY;
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
