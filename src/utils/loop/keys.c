/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:51:23 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

void    key_handler(int key, bool down)
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
	if (key == XK_Up)
		player->looking_up = down;
	if (key == XK_Down)
		player->looking_down = down;
	if (key == XK_e)
		cub3d()->game.minimap.full = down;
	if (key == XK_Escape)
		cub3d_exit(0);
}

int mouse_motion_handler(int x, int y)
{
	t_player	*player;

	player = cub3d()->game.player;
	if (x > W_WIDTH / 2)
		player->looking_right = true;
	else if (x < W_WIDTH / 2)
		player->looking_left = true;
	else
	{
		player->looking_right = false;
		player->looking_left = false;
	}
	if (y > W_HEIGHT / 2)
		player->looking_down = true;
	else if (y < W_HEIGHT / 2)
		player->looking_up = true;
	else
	{
		player->looking_down = false;
		player->looking_up = false;
	}
	return (0);
}

int	key_up_handler(int key)
{
	return (key_handler(key, false), 0);
}

int	key_down_handler(int key)
{
	return (key_handler(key, true), 0);
}
