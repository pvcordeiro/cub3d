/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:38:00 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/18 10:42:03 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

int	window_loop_hook(void *window)
{
	static bool	previous_using_mouse;

	if (((t_ftm_window *)window)->using_mouse != previous_using_mouse)
	{
		previous_using_mouse = ((t_ftm_window *)window)->using_mouse;
		if (previous_using_mouse)
			mlx_mouse_hide(((t_ftm_window *)window)->display, ((t_ftm_window *)window)->win);
		else
			mlx_mouse_show(((t_ftm_window *)window)->display, ((t_ftm_window *)window)->win);
	}
	if (((t_ftm_window *)window)->loop_hook)
		((t_ftm_window *)window)->loop_hook();
	return (0);
}

int window_key_down_hook(int key, void *window)
{
	if (((t_ftm_window *)window)->key_hook)
		((t_ftm_window *)window)->key_hook(key, true);
	return (0);
}

int window_key_up_hook(int key, void *window)
{
	if (((t_ftm_window *)window)->key_hook)
		((t_ftm_window *)window)->key_hook(key, false);
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
