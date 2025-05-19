/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:04:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/19 23:07:13 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	set_fps(t_game *game)
{
	static int	last_fps;

	if (game->fps == last_fps)
		return ;
	last_fps = game->fps;
	free(game->hud.debug.fps);
	game->hud.debug.fps = ft_strf("FPS: %d", game->fps);
}
