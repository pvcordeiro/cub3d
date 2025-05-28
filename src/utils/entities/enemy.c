/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/22 14:37:18 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

void	init_enemy(t_game *game, t_enemy *enemy, char identifier)
{
	init_billboard(game, (t_billboard *)enemy, identifier);
	enemy->billboard.entity.type = ENTITY_ENEMY;
	enemy->idle_sprite = hashmap_get_with_identifier(game->sprites, identifier, "IDLE");
}

t_enemy	*enemy_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_enemy	*enemy;

	(void)window;
	enemy = ft_calloc(1, sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	init_enemy(game, enemy, identifier);
	enemy->billboard.entity.free = free;
	return (enemy);
}
