/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/17 21:32:30 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void	update_frame(t_game *game)
{
	++game->frames;
	if (ft_get_time() - game->last_frame > 1000)
	{
		game->last_frame = ft_get_time();
		game->fps = game->frames;
		game->frames = 0;
	}
}

void	loop(void)
{
	call_entity_frames(cub3d()->game.entities);
	render_game(&cub3d()->window, &cub3d()->game);
	if (cub3d()->game.hud.enabled)
		ftm_draw_rectangle(cub3d()->window.canvas, (t_coords){20, 20, 0, 0}, (t_size){80, 40}, (t_ftm_rectangle){0x55000000, 0x55EFBF04, (t_size){2, 2}});
	ftm_update_window(&cub3d()->window);
	update_frame(&cub3d()->game);
	render_hud(&cub3d()->game);
}
