/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:04:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/27 14:41:47 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_fps(t_game *game)
{
	static int	last_fps;
	t_fps		fps;

	fps = game->fps;
	if (fps.fps == last_fps)
		return ;
	last_fps = fps.fps;
	free(game->hud.debug.fps);
	game->hud.debug.fps = ft_strf("%d", fps.fps);
	game->hud.debug.fps_min = ft_strf("Min: %d", fps.min);
	game->hud.debug.fps_max = ft_strf("Max: %d", fps.max);
	game->hud.debug.fps_limit = ft_strf("Limit: %d", fps.fps_limit);
}

void	render_debug_fps_strs(t_game *game, t_ftm_image *canvas,
	t_coords coords)
{
	coords.x += render_debug_str(game->font, canvas, "FPS", coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.fps,
			coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.fps_min,
			coords) + 5;
	coords.x += render_debug_str(game->font, canvas, game->hud.debug.fps_max,
			coords) + 5;
	render_debug_str(game->font, canvas, game->hud.debug.fps_limit, coords);
}
