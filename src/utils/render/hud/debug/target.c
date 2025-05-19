/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:41:28 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/19 23:12:08 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_target(t_game *game)
{
	if (!game->player->target_entity)
		return ;
	free(game->hud.debug.target);
	game->hud.debug.target = ftm_image_to_str(get_sprite_image(get_entity_sprite(game->player->target_entity, game->player->target_entity_direction)));
}