/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   billboard.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/22 14:37:18 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

void	init_billboard(t_game *game, t_billboard *billboard, char identifier)
{
	init_entity(game, (t_entity *)billboard, identifier);
	billboard->entity.type = ENTITY_BILLBOARD;
	billboard->entity.billboard = true;
	billboard->entity.size = (t_dsize){BILLBOARD_WIDTH, BILLBOARD_HEIGHT};
	billboard->sprite = hashmap_get_with_identifier(game->sprites, billboard->entity.identifier, "SPRITE");
}

t_billboard	*billboard_new(t_game *game, t_ftm_window *window, char identifier)
{
	t_billboard	*billboard;

	(void)window;
	billboard = ft_calloc(1, sizeof(t_billboard));
	if (!billboard)
		return (NULL);
	init_billboard(game, billboard, identifier);
	billboard->entity.free = free;
	return (billboard);
}
