/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/04 13:45:33 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub3d	*cub3d(void)
{
	static t_cub3d	singleton;

	return (&singleton);
}

void	cub3d_exit(int code)
{
	if (cub3d()->window.initialized)
		destroy_window(&cub3d()->window);
	if (cub3d()->map.initialized)
		destroy_map(&cub3d()->map);
	exit(code);
}

int	key_press_frame(int key_code)
{
	t_player	*player;

	if (!cub3d()->map.player)
		return (0);
	player = cub3d()->map.player->private;
	if (key_code == XK_w)
		player->walking_forward = true;
	if (key_code == XK_a)
		player->walking_left = true;
	if (key_code == XK_s)
		player->walking_backward = true;
	if (key_code == XK_d)
		player->walking_right = true;
	if (key_code == XK_Right)
		player->looking_right = !!!false;
	if (key_code == XK_Left)
		player->looking_left = !!!false;
	if (key_code == XK_e)
		cub3d()->map_fullscreen = !cub3d()->map_fullscreen;
	if (key_code == XK_Escape)
		cub3d_exit(0);
	return (0);
}

int	key_release_frame(int key_code)
{
	t_player	*player;

	if (!cub3d()->map.player)
		return (0);
	player = cub3d()->map.player->private;
	if (key_code == XK_w)
		player->walking_forward = false;
	if (key_code == XK_a)
		player->walking_left = false;
	if (key_code == XK_s)
		player->walking_backward = false;
	if (key_code == XK_d)
		player->walking_right = false;
	if (key_code == XK_Right)
		player->looking_right = false;
	if (key_code == XK_Left)
		player->looking_left = false;
	return (0);
}

int	cub3d_loop(void *_)
{
	t_coords	map_coords;
	t_size		map_size;
	(void)_;

	map_coords = (t_coords){0, W_HEIGHT - MINIMAP_HEIGHT, 0, 0};
	map_size = (t_size){MINIMAP_WIDTH, MINIMAP_HEIGHT};
	if (cub3d()->map_fullscreen)
	{
		map_coords = (t_coords){0, 0, 0, 0};
		map_size = (t_size){W_WIDTH, W_HEIGHT};
	}
	clear_canvas(cub3d()->window.canvas);
	call_entity_frames(cub3d()->map.entities);
	render_raycasting_mega(&cub3d()->map, cub3d()->window.canvas);
	render_map(&cub3d()->map, cub3d()->window.canvas, map_coords, map_size);
	mlx_put_image_to_window(cub3d()->window.mlx, cub3d()->window.win,
		cub3d()->window.canvas->img_ptr, 0, 0);
	return (0);
}
