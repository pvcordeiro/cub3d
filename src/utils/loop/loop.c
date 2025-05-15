/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/15 19:13:27 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

void	loop(void)
{
	static t_time	last_frame;
	static int		frames;

	++frames;
	if (ft_get_time() - last_frame > 1000)
	{
		printf("FPS: %d\n", frames);
		last_frame = ft_get_time();
		frames = 0;
	}
	call_entity_frames(cub3d()->game.entities);
	render_game(&cub3d()->window, &cub3d()->game);
	ftm_update_window(&cub3d()->window);
}
