/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:59:12 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/18 17:49:16 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlay.h"

void	render_overlay(t_game *game)
{
	if (!game->hud.enabled)
		return ;
	render_debug(game);
	//TODO render_weapon(game);
	//TODO render_hud(game);
}
