/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:03:13 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 01:51:51 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	set_strs(t_game *game)
{
	set_fps(game);
	set_target(game);
	set_player(game);
}

static void	render_debug_str(t_ftm_font *font, t_ftm_image *canvas, char *str, t_coords coords)
{
	t_ftm_text_config	config;
	int					width;

	if (!str)
		return ;
	config = (t_ftm_text_config){
		str,
		(t_coords){coords.x + 10, coords.y + 10, 0},
		16,
		-5
	};
	width = ftm_get_text_size_prediction(font, config) + 25;
	ftm_draw_rectangle(canvas, coords, (t_size){width, 35}, (t_ftm_rectangle){0x55000000, 0x55EFBF04, (t_size){2, 2}});
	ftm_draw_text(canvas, font, config);
}

static void	render_debug_strs(t_game *game, t_ftm_image *canvas)
{
	render_debug_str(game->font, canvas, game->hud.debug.fps, (t_coords){20, 20, 0});
	render_debug_str(game->font, canvas, game->hud.debug.target, (t_coords){20, 60, 0});
	render_debug_str(game->font, canvas, game->hud.debug.player, (t_coords){20, 100, 0});
}

void	render_debug(t_game *game, t_ftm_image *canvas)
{
	set_strs(game);
	render_debug_strs(game, canvas);
}
