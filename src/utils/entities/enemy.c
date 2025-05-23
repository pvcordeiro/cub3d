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

static void	enemy_frame(t_entity *entity, double delta_time)
{
	((void)entity, (void)delta_time);
}

static void	free_enemy(void *enemy)
{
	free(enemy);
}

static void	*hashmap_get_with_identifier(t_hashmap *hashmap, char identifier, char *rest)
{
	char	*key;
	void	*data;

	key = ft_strdup(rest);
	if (identifier != '1')
		key = (free(key), ft_strf("%c_%s", identifier, rest));
	data = ft_hashmap_get_value(hashmap, key);
	return (free(key), data);
}

t_enemy	*enemy_new(char identifier, t_ftm_window *window, t_game *game)
{
	t_enemy	*enemy;

	(void)window;
	enemy = ft_calloc(1, sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	enemy->billboard.entity.type = ENTITY_ENEMY;
	enemy->billboard.entity.frame = enemy_frame;
	enemy->billboard.entity.free = free_enemy;
	enemy->billboard.entity.hard = true;
	enemy->billboard.entity.billboard = true;
	enemy->billboard.entity.identifier = identifier;
	enemy->billboard.entity.size = (t_size){1, 1};
	enemy->idle_sprite = hashmap_get_with_identifier(game->sprites, identifier, "IDLE");
	return (enemy);
}
