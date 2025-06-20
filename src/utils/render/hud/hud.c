/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:59:12 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/20 16:02:49 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	render_hud(t_game *game, t_ftm_image *canvas, t_character *character)
{
	t_size	stats_size;

	if (!game->hud.enabled)
		return ;
	render_effects(canvas, character);
	stats_size = render_stats(game, canvas, character);
	render_hand_item(canvas, character, stats_size);
	render_minimap(game, canvas, character);
	render_action(game, canvas, character);
	render_debug(game, canvas, character);
}
