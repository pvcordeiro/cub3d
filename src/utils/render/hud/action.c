/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:27:23 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/27 12:18:13 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	render_action(t_game *game, t_ftm_image *canvas)
{
	t_ftm_text_config	text_config;

	if (!game->player
		|| !game->player->billboard.entity.target_entity
		|| !game->player->billboard.entity.target_entity->action)
		return ;
	text_config = (t_ftm_text_config){
		.text = "Press SPACE to interact",
		.coords = (t_coords){0, 0, 0},
		.height = 15,
		.spacing = 0,
		.color = 0xFFDDDDDD
	};
	text_config.coords.x = (canvas->size.width / 2)
		- (ftm_get_text_size_prediction(game->font, text_config) / 2);
	text_config.coords.y = canvas->size.height - 200;
	ftm_draw_text_in_box(canvas, game->font, text_config,
		(t_ftm_rectangle){0x55000000, 0x55EFBF04, (t_size){2, 2}});
}
