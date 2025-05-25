/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:41:28 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/25 19:06:41 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_target(t_game *game)
{
	static t_entity	*last_entity;
	t_entity		*target_entity;

	if (!game->player || !game->player->billboard.entity.target_entity)
		return ;
	target_entity = game->player->billboard.entity.target_entity;
	if (last_entity == target_entity)
		return ;
	(free(game->hud.debug.target_x), free(game->hud.debug.target_y),
		free(game->hud.debug.target_yaw), free(game->hud.debug.target_id),
		free(game->hud.debug.target_type));
	last_entity = target_entity;
	game->hud.debug.target_x = ft_strf("X: %d", (int)target_entity->coords.x);
	game->hud.debug.target_y = ft_strf("Y: %d", (int)target_entity->coords.y);
	game->hud.debug.target_yaw = ft_strf("Yaw: %d", (int)target_entity->coords.yaw);
	game->hud.debug.target_id = ft_strf("ID %c",
		target_entity->identifier);
	game->hud.debug.target_type = ft_strf("Type %d", target_entity->type);
	printf("%d, %zd, %zd\n", get_entity_sprite(target_entity, game->player->billboard.entity.target_entity_direction)->loop, ft_get_time() - get_entity_sprite(target_entity, game->player->billboard.entity.target_entity_direction)->updated_at, get_entity_sprite(target_entity, game->player->billboard.entity.target_entity_direction)->update_delay);
}

void	render_debug_target_strs(t_game *game, t_ftm_image *canvas, t_coords coords)
{
	coords.x += render_debug_str(game->font, canvas, "Target", coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.target_x, coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.target_y, coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.target_yaw, coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.target_id, coords) + 5;
	render_debug_str(game->font, canvas, game->hud.debug.target_type, coords);
}
