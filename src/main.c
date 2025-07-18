/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvcordeiro <pvcordeiro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/29 21:29:50 by pvcordeiro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	load_main_sprite(void)
{
	fte_set(NULL);
	cub3d()->placeholder_image = ftm_image_from_file(cub3d()->window,
		PLACEHOLDER_IMAGE_PATH);
	if (!cub3d()->placeholder_image)
		(fte_set("load placeholder sprite"), fte_assert());
	cub3d()->loading_image = ftm_image_from_file(cub3d()->window,
		LOADING_IMAGE_PATH);
	if (!cub3d()->loading_image)
		(fte_set("load loading sprite"), fte_assert());
}

static void	init_window(void)
{
	t_ftm_window	*window;
	t_size			size;

	size.width = W_WIDTH;
	size.height = W_HEIGHT;
	window = ftm_window_new_e((t_size){size.width, size.height}, W_TITLE);
	fte_assert();
	size = ftm_get_screen_size(window);
	ftm_window_resize_e(window, size);
	window->fullscreen = true;
	ftm_window_notify_fullscreen(window);
	window->loop_hook = loop;
	window->key_hook = key_hook;
	window->exit_hook = cub3d_exit;
	window->mouse_hook = mouse_hook;
	cub3d()->window = window;
}

int	main(int argc, char **argv)
{
	(void)argc;
	fte_storage()->exit = cub3d_exit;
	pthread_mutex_init(&cub3d()->game_mutex, NULL);
	cub3d()->new_map_path = argv[1];
	init_window();
	load_main_sprite();
	fta_init_e();
	ftm_window_loop(cub3d()->window);
}
