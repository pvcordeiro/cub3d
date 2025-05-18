/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:35:24 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/18 17:48:48 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlay.h"

void	render_fps(t_game *game)
{
	static int	last_fps;

	if (game->fps != last_fps)
	{
		last_fps = game->fps;
		free(game->hud.debug.dbg_str);
		game->hud.debug.dbg_str = ft_strf("FPS: %d", game->fps);
	}
	if (game->hud.debug.dbg_str)
		mlx_string_put(cub3d()->window.display, cub3d()->window.win, 38, 45, 0xFFFFFFFF, game->hud.debug.dbg_str);
}
