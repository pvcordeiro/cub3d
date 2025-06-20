/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:58:13 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/19 20:56:39 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	ftm_create_window_e(t_ftm_window *window, t_size size, char *title)
{
	fte_set(NULL);
	window->display = mlx_init();
	if (!window->display)
		return (fte_set("init mlx"));
	window->win = mlx_new_window(window->display,
			size.width, size.height, title);
	if (!window->win)
		return (mlx_destroy_display(window->display),
			fte_set("init window"));
	window->canvas = ftm_image_new(window, size);
	if (!window->canvas)
		return (mlx_destroy_window(window->display, window->win),
			mlx_destroy_display(window->display), fte_set("init canvas"));
	window->size = size;
	window->title = title;
	ftm_window_reload_controllers(window);
}

void	ftm_clear_window(void *data)
{
	t_ftm_window	*window;

	if (!data)
		return ;
	window = (t_ftm_window *)data;
	ft_list_destroy(&window->controllers);
	ftm_free_image(window->canvas);
	mlx_destroy_window(window->display, window->win);
	mlx_destroy_display(window->display);
	free(window->display);
}

void	ftm_free_window(void *data)
{
	if (!data)
		return ;
	ftm_clear_window(data);
	free(data);
}

void	ftm_update_window(t_ftm_window *window)
{
	mlx_put_image_to_window(window->display, window->win,
		window->canvas->img_ptr, 0, 0);
}
