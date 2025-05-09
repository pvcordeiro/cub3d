/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/09 21:59:34 by paude-so         ###   ########.fr       */
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
    double		rotation_speed;
    double		old_dir_x;
    double		old_plane_x;

    (void)y;
    player = cub3d()->game.player;
    movement = x - prev_x;
    if (movement != 0 && player && !player->using_mouse)
    {
        // Apply reduced sensitivity and limit maximum rotation per frame
        rotation_speed = movement * player->mouse_look_sens;
        
        // Cap maximum rotation per frame (prevents jerky movement with sudden large mouse movements)
        double max_rotation = 0.1; // About 5.7 degrees maximum per frame
        if (rotation_speed > max_rotation)
            rotation_speed = max_rotation;
        else if (rotation_speed < -max_rotation)
            rotation_speed = -max_rotation;
            
        // Apply non-linear response for small movements (more precise aiming)
        if (fabs(rotation_speed) < 0.02)
            rotation_speed *= 0.5;
        
        // Rotate direction vector
        old_dir_x = player->dir.x;
        player->dir.x = player->dir.x * cos(rotation_speed) - player->dir.y * sin(rotation_speed);
        player->dir.y = old_dir_x * sin(rotation_speed) + player->dir.y * cos(rotation_speed);
        
        // Rotate camera plane
        old_plane_x = player->plane.x;
        player->plane.x = player->plane.x * cos(rotation_speed) - player->plane.y * sin(rotation_speed);
        player->plane.y = old_plane_x * sin(rotation_speed) + player->plane.y * cos(rotation_speed);
        
        // Update yaw for compatibility with other systems
        player->base.coords.yaw = ft_normalize_angle(atan2(player->dir.y, player->dir.x) * 180.0 / PI);
        
        mlx_mouse_move(cub3d()->window.display, cub3d()->window.win, W_WIDTH / 2, W_HEIGHT / 2);
        prev_x = W_WIDTH / 2;
    }
    return (0);
}
