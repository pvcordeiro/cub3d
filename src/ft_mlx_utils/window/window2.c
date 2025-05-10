/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:52:09 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/10 14:53:22 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	ftm_update_hooks(t_ftm_window *window)
{
	mlx_hook(window->win, KeyPress, KeyPressMask, window_key_down_hook, window);
	mlx_hook(window->win, KeyRelease, KeyReleaseMask, window_key_up_hook, window);
	mlx_hook(window->win, DestroyNotify, KeyPressMask, window_exit_hook, window);
	mlx_hook(window->win, MotionNotify, PointerMotionMask, window_mouse_hook, window);
	mlx_loop_hook(window->display, window_loop_hook, window);
}

void	ftm_window_loop(t_ftm_window *window)
{
	mlx_loop(window->display);
}
