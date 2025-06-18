/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:59:30 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/18 20:21:57 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

#define DAMAGE_EFFECT_DURATION 500
#define USE_EFFECT_DURATION 500

void	render_effects(t_game *game, t_ftm_image *canvas)
{
	t_time	time_since_last_hit;
	t_time	time_since_last_auto_use;
	int		alpha;

	time_since_last_hit = ft_get_time() - game->player->character.last_hit;
	if (time_since_last_hit < DAMAGE_EFFECT_DURATION)
	{
		alpha = 75 * (DAMAGE_EFFECT_DURATION - time_since_last_hit) / DAMAGE_EFFECT_DURATION;
		ftm_draw_rectangle(canvas, (t_coords){0, 0, 0}, canvas->size, (t_ftm_rectangle){
			(alpha << 24) | 0x00FF0000,
			0, (t_size){0, 0}
		});
	}
	time_since_last_auto_use = ft_get_time() - game->player->character.last_auto_use;
	if (time_since_last_auto_use < USE_EFFECT_DURATION)
	{
		alpha = 75 * (USE_EFFECT_DURATION - time_since_last_auto_use) / USE_EFFECT_DURATION;
		ftm_draw_rectangle(canvas, (t_coords){0, 0, 0}, canvas->size, (t_ftm_rectangle){
			(alpha << 24) | 0x00FFFFFF,
			0, (t_size){0, 0}
		});
	}
}
