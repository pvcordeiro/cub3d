/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/22 18:23:59 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void update_frame(t_game *game)
{
    t_time now;

    now = ft_get_time();
    if (!game->fps.beginning)
    {
        game->fps.beginning = now;
        game->fps.last_frame_time = now;
        game->fps.delta_time = DELTA_TIME_START;
    }
    else
    {
        game->fps.delta_time = (now - game->fps.last_frame_time) / 1000.0f;
        game->fps.last_frame_time = now;
    }
    ++game->fps.frame_count;
    if (now - game->fps.fps_update_time > 250)
    {
        game->fps.fps = game->fps.frame_count * 4;
        game->fps.frame_count = 0;
        game->fps.fps_update_time = now;
		if (now - game->fps.beginning < 3000)
		{
			game->fps.min = game->fps.fps;	
			return ;
		}
		if (game->fps.fps > game->fps.max)
			game->fps.max = game->fps.fps;
		if (game->fps.fps < game->fps.min)
			game->fps.min = game->fps.fps;
    }
}

void	loop(void)
{
	call_entity_frames(cub3d()->game.entities, &cub3d()->game.fps);
	render_game(&cub3d()->window, &cub3d()->game);
	ftm_update_window(&cub3d()->window);
	update_frame(&cub3d()->game);
}
