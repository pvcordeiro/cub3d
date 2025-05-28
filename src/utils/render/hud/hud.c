/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:59:12 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/28 17:49:40 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	render_hud(t_game *game, t_ftm_image *canvas)
{
	if (!game->hud.enabled)
		return ;
	render_debug(game, canvas);
	render_action(game, canvas);
	render_stats(game, canvas);
	render_minimap(game, canvas);
}
