/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 16:01:20 by paude-so         ###   ########.fr       */
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
