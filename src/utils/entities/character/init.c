/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 20:47:57 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

void	init_character(t_game *game, t_ftm_window *window, t_character *character, char identifier)
{
	init_billboard(game, window, (t_billboard *)character, identifier);
	character->billboard.entity.type = ENTITY_CHARACTER;
	character->billboard.entity.frame = character_frame;
	character->billboard.entity.clear = clear_character;
	character->billboard.entity.action = character_action;
	character->billboard.entity.shot = character_shot;
	character->death_sprite = ft_calloc(360, sizeof(t_sprite *));
	character->walking_sprite = ft_calloc(360, sizeof(t_sprite *));
	character->hit_sprite = ft_calloc(360, sizeof(t_sprite *));
	fill_3d_sprites_from_game(game, character->walking_sprite, identifier, "WALKING");
	fill_3d_sprites_from_game(game, character->death_sprite, identifier, "DEATH");
	fill_3d_sprites_from_game(game, character->hit_sprite, identifier, "HIT");
	character->_sprite = character->billboard.sprites;
	character->death_sound = hashmap_get_with_identifier(game->sounds, identifier, "DEATH");
	character->hit_sound = hashmap_get_with_identifier(game->sounds, identifier, "HIT");
}

t_character	*character_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_character	*character;

	character = ft_calloc(1, sizeof(t_character));
	if (!character)
		return (NULL);
	init_character(game, window, character, identifier);
	return (character);
}
