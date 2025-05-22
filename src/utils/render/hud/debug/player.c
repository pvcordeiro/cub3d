/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:49:57 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/22 23:08:07 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_player(t_game *game)
{
	if (!game->player)
		return ;
	(free(game->hud.debug.player_x) ,free(game->hud.debug.player_y),
		free(game->hud.debug.player_yaw));
	game->hud.debug.player_x = ft_strf("X: %d", (int)game->player->entity.coords.x);
	game->hud.debug.player_y = ft_strf("Y: %d", (int)game->player->entity.coords.y);
	game->hud.debug.player_yaw = ft_strf("Yaw: %d",
		(int)game->player->entity.coords.yaw);
}

void	render_debug_player_strs(t_game *game, t_ftm_image *canvas, t_coords coords)
{
	coords.x += render_debug_str(game->font, canvas, "Player", coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.player_x, coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.player_y, coords) + 5;
	render_debug_str(game->font, canvas, game->hud.debug.player_yaw, coords);
}
