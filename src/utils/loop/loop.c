/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 14:58:37 by afpachec         ###   ########.fr       */
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
	static bool	playing_bg_music;
	t_game		*prev_game;

	if (cub3d()->curr_map != cub3d()->game->map)
	{
		pthread_mutex_lock(&cub3d()->game_mutex);
		prev_game = cub3d()->game;
		cub3d()->game = game_new(&cub3d()->window, cub3d()->curr_map);
		free_game(prev_game);
		free_map(cub3d()->prev_map);
		cub3d()->prev_map = NULL;
		playing_bg_music = false;
		pthread_mutex_unlock(&cub3d()->game_mutex);
	}
	if (!cub3d()->curr_map)
		return ;
	if (!playing_bg_music)
		fta_play(cub3d()->game->background_sound);
	playing_bg_music = true;
	pthread_mutex_lock(&cub3d()->game_mutex);
	call_entity_frames(cub3d()->game, &cub3d()->game->fps);
	update_walls_matrix(cub3d()->game);
	update_billboards_vec(cub3d()->game);
	render_players_game(cub3d()->game, &cub3d()->window);
	update_frame(cub3d()->game);
	process_fps_limit(cub3d()->game);
	pthread_mutex_unlock(&cub3d()->game_mutex);
}
