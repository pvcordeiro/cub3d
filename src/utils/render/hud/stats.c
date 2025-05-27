/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:14:35 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/27 14:44:31 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	render_stats(t_game *game, t_ftm_image *canvas)
{
	t_size		stats_size;
	t_ftm_image	*image;
	int			index;

	if (!game->hud.stats.states)
		return ;
	stats_size = (t_size){canvas->size.width, canvas->size.width / 8};
	index = (int)(game->hud.stats.states
			* ((float)game->player->billboard.entity.health
				/ game->player->billboard.entity.max_health));
	index = game->hud.stats.states - index;
	if (index >= game->hud.stats.states)
		index = game->hud.stats.states - 1;
	if (index < 0)
		index = 0;
	image = get_sprite_image(ft_list_index(game->hud.stats.states_list,
				index)->data);
	ftm_put_image_to_canvas(canvas, image,
		(t_ftm_pitc_config){
		(t_coords){0, canvas->size.height - stats_size.height, 0},
		false, (t_coords){0, 0, 0}, (t_coords){0, 0, 0},
		true, stats_size, NULL, NULL});
}
