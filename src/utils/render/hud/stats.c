/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:14:35 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/25 22:23:03 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "hud.h"

void	render_stats(t_game *game, t_ftm_image *canvas)
{
	t_size		stats_size;
	t_sprite	*sprite;

	sprite = ((t_sprite *)ft_hashmap_get_value(game->sprites, "STATS_HUD_1_SPRITE"));
	stats_size = (t_size){canvas->size.width, canvas->size.width / 8};
	ftm_put_image_to_canvas(canvas, get_sprite_image(sprite),
		(t_ftm_pitc_config){
		(t_coords){0, canvas->size.height - stats_size.height, 0},
		false, (t_coords){0, 0, 0},
		(t_coords){0, 0, 0}, true,
		stats_size,
		NULL, NULL });
}
