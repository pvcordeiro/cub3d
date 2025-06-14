/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/15 14:17:31 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static double	get_delta_time(void)
{
	static struct timeval	last_time = {0, 0};
	struct timeval			current_time;
	double					delta;

	if (last_time.tv_sec == 0 && last_time.tv_usec == 0)
	{
		gettimeofday(&last_time, NULL);
		return (FPS60);
	}
	gettimeofday(&current_time, NULL);
	delta = (current_time.tv_sec - last_time.tv_sec) + (current_time.tv_usec
			- last_time.tv_usec) / 1000000.0;
	last_time = current_time;
	return (delta);
}

void	loop(void)
{
	double	delta_time;

	mlx_clear_window(cub3d()->window.display, cub3d()->window.win);
	delta_time = get_delta_time();
	update_fps_data(&cub3d()->game.fps, delta_time);
	call_entity_frames(cub3d()->game.entities, delta_time);
	render_game(&cub3d()->window, &cub3d()->game);
}
