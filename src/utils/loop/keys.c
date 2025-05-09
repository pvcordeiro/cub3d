/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/09 22:35:36 by paude-so         ###   ########.fr       */
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
	if (key == XK_Tab)
		cub3d()->game.minimap.full = down;
	if (key == XK_Escape)
		cub3d_exit(0);
	if (key == XK_m && down)
		player->using_mouse = !player->using_mouse;
	if (key == XK_Shift_L && down)
		player->move_speed = PLAYER_SPRINTING_SPEED;
	if (key == XK_Shift_L && !down)
		player->move_speed = PLAYER_SPEED;
}

int	key_up_handler(int key)
{
	return (key_handler(key, false), 0);
}

int	key_down_handler(int key)
{
	return (key_handler(key, true), 0);
}

int	mouse_aim(int x, int y)
{
	static int	prev_x = W_WIDTH / 2;
	int			movement;
	t_player	*player;
	double		adjusted_movement;

	(void)y;
	player = cub3d()->game.player;
	movement = x - prev_x;
	if (movement != 0 && player && !player->using_mouse)
	{
		adjusted_movement = movement;
		if (abs(movement) < 10)
			adjusted_movement = movement * (0.5 + (abs(movement) / 20.0));
		player->base.coords.yaw += adjusted_movement * player->mouse_look_sens;
		player->base.coords.yaw = ft_normalize_angle(player->base.coords.yaw);
		mlx_mouse_move(cub3d()->window.display, cub3d()->window.win, W_WIDTH / 2, W_HEIGHT / 2);
		prev_x = W_WIDTH / 2;
	}
	return (0);
}
