/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/24 02:31:23 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void	player_keys(t_player *player, int key, bool down)
{
	if (!player)
		return ;
	if (key == XK_w)
		player->walking_forward = down;
	if (key == XK_a)
		player->walking_left = down;
	if (key == XK_s)
		player->walking_backward = down;
	if (key == XK_d)
		player->walking_right = down;
	if (key == XK_Right)
		player->looking_right = down;
	if (key == XK_Left)
		player->looking_left = down;
	if (key == XK_space)
		player->action = down;
	if (key == XK_Shift_L || key == XK_Shift_R)
		player->sprinting = down;
}

static void	hud_debug_keys(t_hud_debug *hud_debug, int key, bool down)
{
	t_size	map_size;

	if (key == XK_F3 && down)
		hud_debug->enabled = !hud_debug->enabled;
	if (!hud_debug->enabled)
		return ;
	if (key == XK_c && down)
		cub3d()->game.camera.rays /= 1.5;
	if (key == XK_v && down)
		cub3d()->game.camera.rays = PLAYER_RAYS;
	if (key == XK_b && down)
		cub3d()->game.player->billboard.entity.hard = !cub3d()->game.player->billboard.entity.hard;
	if (key == XK_n && down)
	{
		map_size = cub3d()->game.map->size;
		cub3d()->game.player->billboard.entity.coords = (t_coords){map_size.width / 2,
		map_size.height / 2, 0};
	}
	if (key == XK_m && down)
		cub3d()->window.using_mouse = !cub3d()->window.using_mouse;
	if (key == XK_k && down)
		cub3d()->game.fps.fps_limit /= 1.5;
	if (key == XK_l && down)
		cub3d()->game.fps.fps_limit = FPS_LIMIT;
	if (key == XK_o && down)
		cub3d()->game.camera.fov /= 1.2;
	if (key == XK_p && down)
		cub3d()->game.camera.fov = PLAYER_FOV;
}

static void	hud_keys(t_hud *hud, int key, bool down)
{
	if (key == XK_h && down)
		hud->enabled = !hud->enabled;
	if (!hud->enabled)
		return ;
	hud_debug_keys(&hud->debug, key, down);
}

void	key_hook(int key, bool down)
{
	player_keys(cub3d()->game.player, key, down);
	hud_keys(&cub3d()->game.hud, key, down);
	if (key == XK_Tab)
		cub3d()->game.minimap.full = down;
	if (key == XK_Escape)
		cub3d_exit(0);
}
