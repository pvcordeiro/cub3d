/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvcordeiro <pvcordeiro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:21:31 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/07 10:27:17 by pvcordeiro       ###   ########.fr       */
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
	cub3d()->game.camera.rays = size.width; //TODO make it so that all the items use canvas.width instead of having to set manually
}

void	ftm_window_fullscreen(t_ftm_window *window)
{
	t_xvar *xvar;

	xvar = (void *)window->display;
	if (!window->fullscreen)
	ftm_window_resize_e(window, (t_size){XDisplayWidth(xvar->display,
		xvar->screen), XDisplayHeight(xvar->display, xvar->screen)});
	else
		ftm_window_resize_e(window, (t_size){W_WIDTH, W_HEIGHT});
}
