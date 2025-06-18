/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/18 21:36:56 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void update_frame(t_game *game)
{
	t_time now;

	now = ft_get_time();
	game->fps.delta_time = (now - game->fps.last_frame_time) / 1000.0f;
	game->fps.last_frame_time = now;
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

static void process_fps_limit(t_game *game)
{
	static t_time	previous_time;
	t_time			current_time;
	t_time			elapsed;
	double			target_frame_time;

	if (!previous_time)
	{
		previous_time = ft_get_time();
		return;
	}
	target_frame_time = 1000.0 / game->fps.fps_limit;
	current_time = ft_get_time();
	elapsed = current_time - previous_time;
	if (elapsed < target_frame_time)
		ft_sleep(target_frame_time - elapsed);
	previous_time = ft_get_time();
}

void	loop(void)
{
	call_entity_frames(cub3d()->game.entities, &cub3d()->game.fps);
	render_game(&cub3d()->game, cub3d()->window.canvas,
		(t_character *)cub3d()->game.player);
	ftm_update_window(&cub3d()->window);
	update_frame(&cub3d()->game);
	process_fps_limit(&cub3d()->game);
}
