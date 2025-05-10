/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:06:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/10 11:35:47 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

int	mouse_motion_handler(int x, int y)
{
	t_player		*player;
	t_ftm_window	*window;
	double			movement;

	(void)y;
	window = &cub3d()->window;
	if (!window->using_mouse)
		return (0);
	mlx_mouse_move(window->display, window->win, window->size.width / 2, window->size.height / 2);
	movement = x - (window->size.width / 2);
	if (fabs(movement) < 10)
		movement = movement * (0.5 + (fabs(movement) / 20.0));
	player = cub3d()->game.player;
	if (player)
		player->mouse_moviment = movement;
	return (0);
}
