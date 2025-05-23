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

static void	billboard_frame(t_entity *entity, double delta_time)
{
	((void)entity, (void)delta_time);
}

static void	free_billboard(void *billboard)
{
	free(billboard);
}

t_billboard	*billboard_new(char identifier, t_ftm_window *window, t_game *game)
{
	t_billboard	*billboard;

	(void)window;
	billboard = ft_calloc(1, sizeof(t_billboard));
	if (!billboard)
		return (NULL);
	billboard->entity.type = ENTITY_BILLBOARD;
	billboard->entity.frame = billboard_frame;
	billboard->entity.free = free_billboard;
	billboard->entity.hard = true;
	billboard->entity.billboard = true;
	billboard->entity.identifier = identifier;
	billboard->entity.size = (t_size){1, 1};
	billboard->sprite = hashmap_get_with_identifier(game->sprites, identifier, "SPRITE");
	return (billboard);
}
