/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 22:22:55 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

void	cub3d_exit(int code)
{
	destroy_map(cub3d()->curr_map);
	free_game(&cub3d()->game);
	if (cub3d()->master_sprites.initialized)
		destroy_master_sprites(&cub3d()->master_sprites);
	if (cub3d()->window.initialized)
		ftm_free_window(&cub3d()->window);
	exit(code);
}

int	loop(void *_)
{
	(void)_;
	ftm_image_clear(cub3d()->window.canvas);
	call_entity_frames(cub3d()->game.entities);
	render_game(&cub3d()->window, &cub3d()->game);
	ftm_update_window(&cub3d()->window);
	return (0);
}
