/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/14 23:01:50 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

void    key_hook(int key, bool down)
{
	t_player	*player;

	player = cub3d()->game.player;
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
	if (key == XK_Tab)
		cub3d()->game.minimap.full = down;
	if (key == XK_Escape)
		cub3d_exit(0);
}

