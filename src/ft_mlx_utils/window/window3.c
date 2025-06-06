/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:21:31 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/06 22:40:44 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	ftm_window_resize_e(t_ftm_window *window, t_size size)
{
	char	*title;

	title = window->title;
	mlx_destroy_window(window->display, window->win);
	window->win = mlx_new_window(window->display,
		size.width, size.height, title);
	ftm_update_hooks(window);
	ftm_free_image(window->canvas);
	window->canvas = ftm_image_new(window, size);
}

void	ftm_window_fullscreen(t_ftm_window *window)
{
	t_xvar *xvar;

	xvar = (void *)window->display;
	ftm_window_resize_e(window, (t_size){XDisplayWidth(xvar->display,
		xvar->screen), XDisplayHeight(xvar->display, xvar->screen)});
}
