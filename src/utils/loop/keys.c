/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/07 12:20:38 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

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
		cub3d()->game.camera.fov *= 1.2;
	if (key == XK_y && down)
		cub3d()->game.player->billboard.entity.health /= 1.2;
	if (key == XK_u && down)
		cub3d()->game.player->billboard.entity.health = cub3d()->game.player->billboard.entity.max_health;
}

static void	hud_minimap_keys(int key, bool down)
{
	if (key == XK_Tab)
		cub3d()->game.hud.minimap.full = down;
	if (key == XK_equal && down && cub3d()->game.hud.minimap.zoom_level < 5.0)
		cub3d()->game.hud.minimap.zoom_level += 0.5;
	if (key == XK_minus && down && cub3d()->game.hud.minimap.zoom_level > 1.0)
		cub3d()->game.hud.minimap.zoom_level -= 0.5;
	if (key == XK_0 && down)
		cub3d()->game.hud.minimap.zoom_level = 5.0;
}

static void	hud_keys(t_hud *hud, int key, bool down)
{
	int	*fullscreen;
	t_ftm_window *window;

	window = &cub3d()->window;
	fullscreen = &window->fullscreen;
    if (key == XK_h && down)
        hud->enabled = !hud->enabled;
    if (key == XK_F11 && down)
	{
		ftm_window_fullscreen(window);
		// ft_ext_fullscreen((t_xvar *)window->display, (t_win_list *)window->win);
		set_window_fullscreen((t_xvar *)window->display, (t_win_list *)window->win, fullscreen);
	}
	if (!hud->enabled)
		return ;
	hud_debug_keys(&hud->debug, key, down);
	hud_minimap_keys(key, down);
}

void	key_hook(int key, bool down)
{
	call_entity_keys(cub3d()->game.entities, key, down);
	hud_keys(&cub3d()->game.hud, key, down);
	if (key == XK_Escape)
		cub3d_exit(0);
}
