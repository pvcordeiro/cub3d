/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 02:07:13 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/27 20:08:57 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_entities(t_game *game)
{
	static t_time	last_check;

	if (ft_get_time() - last_check < 1000)
		return ;
	free(game->hud.debug.entities_count);
	game->hud.debug.entities_count = ft_strf("%d",
			ft_list_size(game->entities));
}

void	render_debug_entities_strs(t_game *game, t_ftm_image *canvas,
	t_coords coords)
{
	coords.x += render_debug_str(game, canvas, "Entities", coords) + 5;
	render_debug_str(game, canvas, game->hud.debug.entities_count,
		coords);
}
