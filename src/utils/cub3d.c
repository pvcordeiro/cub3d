/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/30 10:18:21 by afpachec         ###   ########.fr       */
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

	if (!cub3d()->player)
		return (0);
	player = cub3d()->player->private;
	if (key_code == KEY_W)
		player->walking_forward = true;
	if (key_code == KEY_A)
		player->walking_left = true;
	if (key_code == KEY_S)
		player->walking_backward = true;
	if (key_code == KEY_D)
		player->walking_right = true;
	if (key_code == KEY_ESC)
		cub3d_exit(0);
	return (0);
}

int	key_release_frame(int key_code)
{
	t_player	*player;

	if (!cub3d()->player)
		return (0);
	player = cub3d()->player->private;
	if (key_code == KEY_W)
		player->walking_forward = false;
	if (key_code == KEY_A)
		player->walking_left = false;
	if (key_code == KEY_S)
		player->walking_backward = false;
	if (key_code == KEY_D)
		player->walking_right = false;
	return (0);
}

int	cub3d_loop(void *_)
{
	(void)_;
	call_entity_frames(cub3d()->map.entities);
	render_map(&cub3d()->map, cub3d()->window.canvas, (t_coords){0, W_HEIGHT - MINIMAP_HEIGHT, 0, 0}, (t_size){MINIMAP_WIDTH, MINIMAP_HEIGHT});
	mlx_put_image_to_window(cub3d()->window.mlx, cub3d()->window.win,
		cub3d()->window.canvas->img_ptr, 0, 0);
	return (0);
}
