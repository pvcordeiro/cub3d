/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:03:13 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/19 23:20:48 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	set_strs(t_game *game)
{
	set_fps(game);
	set_target(game);
}

static void	render_debug_str(t_ftm_image *canvas, char *str, t_coords coords)
{
	t_size	rectangle_size;

	if (!str)
		return ;
	rectangle_size = (t_size){ft_strlen(str) * 10, 35};
	ftm_draw_rectangle(canvas, coords, rectangle_size, (t_ftm_rectangle){0x55000000, 0x55EFBF04, (t_size){2, 2}});
	(void)str, (void)coords;
}

void	render_debug(t_game *game, t_ftm_image *canvas)
{
	set_strs(game);
	render_debug_str(canvas, game->hud.debug.fps, (t_coords){20, 20, 0});
	render_debug_str(canvas, game->hud.debug.target, (t_coords){20, 60, 0});
}
