/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:41:28 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/20 15:38:41 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_target(t_game *game)
{
	if (!game->player->entity.target_entity)
		return ;
	free(game->hud.debug.target);
	game->hud.debug.target = ftm_image_to_str(get_sprite_image(get_entity_sprite(game->player->entity.target_entity, game->player->entity.target_entity_direction)));
}