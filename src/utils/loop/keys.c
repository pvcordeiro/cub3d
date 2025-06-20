/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 18:01:23 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

void	key_hook(t_ftm_key_hook_values khv)
{
	call_entity_keys(cub3d()->game.entities, khv);
	if (khv.key == XK_Escape)
		cub3d_exit(0);
	if (khv.key == XK_F3 && khv.down)
		cub3d()->game.hud.debug_enabled = !cub3d()->game.hud.debug_enabled;
	if (khv.key == XK_F2 && khv.down)
		cub3d()->game.hud.stats_enabled = !cub3d()->game.hud.stats_enabled;
	if (khv.key == XK_F4 && khv.down)
		cub3d()->game.hud.minimap_enabled = !cub3d()->game.hud.minimap_enabled;
	if (khv.key == XK_F5 && khv.down)
		cub3d()->game.hud.action_enabled = !cub3d()->game.hud.action_enabled;
	if (khv.key == XK_F6 && khv.down)
		cub3d()->game.hud.enabled = !cub3d()->game.hud.enabled;
	if (khv.key == XK_F1 && khv.down)
		ftm_window_toggle_fullscreen(&cub3d()->window, (t_size){W_WIDTH, W_HEIGHT});
}
