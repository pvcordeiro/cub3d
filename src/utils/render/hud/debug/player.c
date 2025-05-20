/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 01:49:57 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 01:52:37 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_player(t_game *game)
{
	if (!game->player)
		return ;
	free(game->hud.debug.player);
	game->hud.debug.player = ft_strf("X: %d | Y: %d | Yaw: %d",
		(int)game->player->base.coords.x, (int)game->player->base.coords.y,
		(int)game->player->base.coords.yaw);;
}
