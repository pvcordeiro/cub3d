/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:59:12 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/18 20:55:11 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	render_hud(t_game *game, t_ftm_image *canvas, t_character *character)
{
	if (!game->hud.enabled)
		return ;
	render_effects(canvas, character);
	render_hand_item(canvas, character);
	render_stats(game, canvas, character);
	render_minimap(game, canvas, character);
	render_action(game, canvas, character);
	render_debug(game, canvas, character);
}
