/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 21:51:23 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void	update_frame(t_game *game)
{
	t_time	now;
	
	now = ft_get_time();
	if (!game->fps.beginning)
		game->fps.beginning = ft_get_time();
	++game->fps.frame_count;
	if (now - game->fps.last_frame_update > 250)
	{
		game->fps.last_frame_update = now;
		game->fps.fps = game->fps.frame_count * 4;
		game->fps.frame_count = 0;
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
	call_entity_frames(cub3d()->game.entities);
	render_game(&cub3d()->window, &cub3d()->game);
	ftm_update_window(&cub3d()->window);
	update_frame(&cub3d()->game);
}
