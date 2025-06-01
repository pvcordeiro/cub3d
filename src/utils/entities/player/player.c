/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/01 19:01:13 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	init_player(t_game *game, t_player *player, char identifier)
{
	ft_hashmap_set(game->map->types, "N_CONTROLLER", "PLAYER", NULL);
	ft_hashmap_set(game->map->types, "S_CONTROLLER", "PLAYER", NULL);
	ft_hashmap_set(game->map->types, "W_CONTROLLER", "PLAYER", NULL);
	ft_hashmap_set(game->map->types, "E_CONTROLLER", "PLAYER", NULL);
	init_billboard(game, (t_billboard *)player, identifier);
	player->billboard.entity.type = ENTITY_PLAYER;
	if (identifier == 'N')
		player->billboard.entity.coords.yaw = 270.0;
	else if (identifier == 'S')
		player->billboard.entity.coords.yaw = 90.0;
	else if (identifier == 'W')
		player->billboard.entity.coords.yaw = 180.0;
	player->billboard.entity.max_health = 100;
	player->billboard.entity.health = player->billboard.entity.max_health;
	player->billboard.entity.hitbox_radius = PLAYER_HITBOX_RADIUS;
	player->billboard.entity.collision_sound = ft_hashmap_get_value(game->sounds, "COLLISION");
}

t_player	*player_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_player	*player;

	(void)window;
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	init_player(game, player, identifier);
	player->billboard.entity.free = free;
	return (player);
}
