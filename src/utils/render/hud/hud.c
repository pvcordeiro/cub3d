/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:59:12 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/18 20:02:52 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	render_hud(t_game *game, t_ftm_image *canvas)
{
	if (!game->hud.enabled)
		return ;
	render_effects(game, canvas);
	render_hand_item(game, canvas);
	render_stats(game, canvas);
	render_minimap(game, canvas);
	render_action(game, canvas);
	render_debug(game, canvas);
}
