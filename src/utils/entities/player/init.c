/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 17:21:21 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	set_keys(t_game *game, char identifier)
{
	char	*identifiers;
	char	*key;
	int		i;

	identifiers = "NSWE";
	i = -1;
	key = NULL;
	while (identifiers[++i])
	{
		key = (free(key), ft_strf("%c_CONTROLLER", identifier));
		if (key && !ft_hashmap_get_value(game->map->types, key))
			ft_hashmap_set(game->map->types, key, "PLAYER", NULL);
		key = (free(key), ft_strf("%c_MAX_HEALTH", identifier));
		if (key && !ft_hashmap_get_value(game->map->types, key))
			ft_hashmap_set(game->map->types, key,
				ft_hashmap_get_value(game->map->types, "MAX_HEALTH"), NULL);
	}
}

void	init_player(t_game *game, t_ftm_window *window, t_player *player, char identifier)
{
	set_keys(game, identifier);
	init_billboard(game, window, (t_billboard *)player, identifier);
	player->billboard.entity.type = ENTITY_PLAYER;
	player->billboard.entity.frame = player_frame;
	player->billboard.entity.clear = clear_player;
	player->billboard.entity.action = player_action;
	player->billboard.entity.action = player_shot;
	if (identifier == 'N')
		player->billboard.entity.coords.yaw = 270.0;
	else if (identifier == 'S')
		player->billboard.entity.coords.yaw = 90.0;
	else if (identifier == 'W')
		player->billboard.entity.coords.yaw = 180.0;
	player->billboard.entity.size = (t_dsize){PLAYER_WIDTH, PLAYER_HEIGHT};
	player->billboard.entity.collision_sound = ft_hashmap_get_value(game->sounds, "COLLISION");
}

t_player	*player_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	init_player(game, window, player, identifier);
	return (player);
}
