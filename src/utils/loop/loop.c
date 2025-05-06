/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 20:41:56 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

void	cub3d_exit(int code)
{
	if (cub3d()->game.map->initialized)
		destroy_map(cub3d()->game.map);
	if (cub3d()->master_sprites.initialized)
		destroy_master_sprites(&cub3d()->master_sprites);
	if (cub3d()->window.initialized)
		ftm_free_window(&cub3d()->window);
	exit(code);
}

static void	render_to_canvas(t_image *canvas, t_game *game)
{
	t_coords	map_coords;
	t_size		map_size;

	map_coords = (t_coords){0, W_HEIGHT - W_HEIGHT * MINIMAP_HEIGHT__MULTIPLIER, 0, 0};
	map_size = (t_size){W_WIDTH * MINIMAP_WIDTH_MULTIPLIER, W_HEIGHT * MINIMAP_HEIGHT__MULTIPLIER};
	if (cub3d()->map_fullscreen)
	{
		map_coords = (t_coords){0, 0, 0, 0};
		map_size = (t_size){W_WIDTH, W_HEIGHT};
	}
	render_ceiling_and_floor(game, canvas);
	render_raycasting_mega(game, canvas);
	render_map(game, canvas, map_coords, map_size);
}

int	loop(void *_)
{
	(void)_;
	ftm_image_clear(cub3d()->window.canvas);
	call_entity_frames(cub3d()->game.entities);
	render_to_canvas(cub3d()->window.canvas, &cub3d()->game);
	ftm_update_window(&cub3d()->window);
	return (0);
}
