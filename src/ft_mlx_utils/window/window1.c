/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:38:00 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/09 19:25:46 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

int	window_loop_hook(void *data)
{
	static bool	previous_using_mouse;
	t_ftm_window *window;

	window = data;
	if (window->using_mouse != previous_using_mouse)
	{
		previous_using_mouse = window->using_mouse;
		if (previous_using_mouse)
			mlx_mouse_hide(window->display, window->win);
		else
			mlx_mouse_show(window->display, window->win);
	}
	if (window->loop_hook)
		window->loop_hook();
	return (0);
}

int window_key_down_hook(int key, void *window)
{
	if (((t_ftm_window *)window)->key_hook)
		((t_ftm_window *)window)->key_hook(key, (t_coords){0}, true);
	return (0);
}

int window_key_up_hook(int key, void *window)
{
	if (((t_ftm_window *)window)->key_hook)
		((t_ftm_window *)window)->key_hook(key, (t_coords){0}, false);
	return (0);
}

int window_mouse_down_hook(int key, int x, int y, void *window)
{
	if (((t_ftm_window *)window)->key_hook
		&& ((t_ftm_window *)window)->using_mouse)
		((t_ftm_window *)window)->key_hook(key, (t_coords){x, y, 0}, true);
	return (0);
}

int window_mouse_up_hook(int key, int x, int y, void *window)
{
	if (((t_ftm_window *)window)->key_hook
		&& ((t_ftm_window *)window)->using_mouse)
		((t_ftm_window *)window)->key_hook(key, (t_coords){x, y, 0}, false);
	return (0);
}

int window_exit_hook(void *window)
{
	if (((t_ftm_window *)window)->exit_hook)
		((t_ftm_window *)window)->exit_hook(0);
	return (0);
}

int window_mouse_hook(int x, int y, void *window)
{
	if (((t_ftm_window *)window)->mouse_hook)
		((t_ftm_window *)window)->mouse_hook((t_coords){x, y, 0});
	return (0);
}
