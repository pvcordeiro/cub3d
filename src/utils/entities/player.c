/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/29 14:01:42 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	player_looks(t_entity *entity, t_player *player)
{
	if (player->looking_left)
		entity->yaw -= PLAYER_TURN_SPEED;
	else if (player->looking_right)
		entity->yaw += PLAYER_TURN_SPEED;
	entity->yaw = normalize_angle(entity->yaw);
}

static void	player_walk(t_entity *entity, double angle)
{
	double	angle_radians;

	angle_radians = normalize_angle(angle) * (M_PI / 180.0);
	entity->x += PLAYER_SPEED * cos(angle_radians);
	entity->y += PLAYER_SPEED * sin(angle_radians);
}

static void	player_walks(t_entity *entity, t_player *player)
{
	if (player->walking_forward)
		player_walk(entity, entity->yaw);
	if (player->walking_left)
		player_walk(entity, entity->yaw - 90.0);
	if (player->walking_backward)
		player_walk(entity, entity->yaw + 180.0);
	if (player->walking_right)
		player_walk(entity, entity->yaw + 90.0);
}

static void	player_frame(t_entity *entity)
{
	t_player	*player;

	player = (t_player *)(entity->private);
	player_looks(entity, player);
	player_walks(entity, player);
}

static void	free_player(void *entity)
{
	free(((t_entity *)entity)->private);
	free(entity);
}

t_entity	*entity_player_new(char direction)
{
	t_entity	*entity;
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	entity = entity_new(ENTITY_PLAYER, player);
	if (!entity)
		return (free(player), NULL);
	entity->frame = player_frame;
	entity->free = free_player;
	if (direction == 'S')
		entity->yaw = 180.0;
	else if (direction == 'E')
		entity->yaw = 90.0;
	else if (direction == 'W')
		entity->yaw = 270.0;
	return (entity);
}
