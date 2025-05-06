/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:20:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 14:21:50 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

void	cub3d_exit(int code)
{
	if (cub3d()->map.initialized)
		destroy_map(&cub3d()->map);
	if (cub3d()->master_sprites.initialized)
		destroy_master_sprites(&cub3d()->master_sprites);
	if (cub3d()->window.initialized)
		destroy_window(&cub3d()->window);
	exit(code);
}

static void	render_to_canvas(t_image *canvas, t_map *map)
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
	render_ceiling_and_floor(map, canvas);
	render_raycasting_mega(map, canvas);
	render_map(map, canvas, map_coords, map_size);
}

int	loop(void *_)
{
	(void)_;
	clear_canvas(cub3d()->window.canvas);
	call_entity_frames(cub3d()->map.entities);
	render_to_canvas(cub3d()->window.canvas, &cub3d()->map);
	mlx_put_image_to_window(cub3d()->window.mlx, cub3d()->window.win,
		cub3d()->window.canvas->img_ptr, 0, 0);
	return (0);
}
