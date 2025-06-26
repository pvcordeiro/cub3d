/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/26 15:05:55 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	load_main_sprite_e(void)
{
	fte_set(NULL);
	cub3d()->placeholder_image = ftm_image_from_file(&cub3d()->window,
		PLACEHOLDER_IMAGE_PATH);
	if (!cub3d()->placeholder_image)
		return (fte_set("load placeholder sprite"));
	cub3d()->loading_image = ftm_image_from_file(&cub3d()->window,
		LOADING_IMAGE_PATH);
	if (!cub3d()->loading_image)
		return (fte_set("load loading sprite"));
}

int	main(int argc, char **argv)
{
	(void)argc;
	fte_storage()->exit = cub3d_exit;
	pthread_mutex_init(&cub3d()->game_mutex, NULL);
	cub3d()->curr_map = parse_map_e(argv[1]);
	fte_assert();
	ftm_create_window_e(&cub3d()->window, (t_size){W_WIDTH, W_HEIGHT}, W_TITLE);
	fte_assert();
	load_main_sprite_e();
	fte_assert();
	fta_init_e();
	cub3d()->window.loop_hook = loop;
	cub3d()->window.key_hook = key_hook;
	cub3d()->window.exit_hook = cub3d_exit;
	cub3d()->window.mouse_hook = mouse_hook;
	ftm_window_loop(&cub3d()->window);
}
