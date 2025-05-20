/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:49:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 15:41:41 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	render_ceiling_and_floor(t_game *game, t_ftm_image *canvas)
{
    ftm_draw_rectangle(canvas, (t_coords){0, 0, 0}, 
        (t_size){W_WIDTH, W_HEIGHT / 2}, (t_ftm_rectangle){game->environment.ceiling_color, game->environment.ceiling_color, (t_size){1, 1}});
    ftm_draw_rectangle(canvas, (t_coords){0, W_HEIGHT / 2, 0}, 
        (t_size){W_WIDTH, W_HEIGHT / 2}, (t_ftm_rectangle){game->environment.floor_color, game->environment.floor_color, (t_size){1, 1}});
}

void	render_game(t_ftm_window *window, t_game *game)
{
	t_coords	map_coords;
	t_size		map_size;

	map_coords = (t_coords){0, 0, 0};
	map_size = window->size;
	if (!game->minimap.full)
	{
		map_coords = game->minimap.coords;
		map_size = game->minimap.size;
	}
	render_ceiling_and_floor(game, window->canvas);
	render_hud(game, window->canvas);
	render_minimap(game, window->canvas, map_coords, map_size);
}
