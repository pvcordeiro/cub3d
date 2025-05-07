/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 23:51:50 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	exit_game(void)
{
	cub3d_exit(0);
	return (0);
}

static void	load_placeholder_sprite_e(t_ftm_window *window, t_sprite *placeholder)
{
	t_list	*list;
	t_ftm_image	*image;

	fte_set(ERROR_NO_ERROR);
	list = NULL;
	image = ftm_image_from_file(window, PLACEHOLDER_IMAGE_PATH);
	if (!image)
		return (fte_set(ERROR_LOAD_PLACEHOLDER_SPRITE));
	ft_list_add(&list, image, ftm_free_image);
	init_sprite(placeholder, list, PLACEHOLDER_SPRITE_UPDATE_DELAY);
}

int mouse_motion_handler(int x, int y);
int	main(int argc, char **argv)
{
	(void)argc;
	fte_storage()->exit = cub3d_exit;
	ftm_create_window_e(&cub3d()->window, (t_size){W_WIDTH, W_HEIGHT}, W_TITLE);
	fte_assert();
	load_placeholder_sprite_e(&cub3d()->window, &cub3d()->placeholder);
	fte_assert();
	cub3d()->curr_map = parse_map_e(argv[1]);
	fte_assert();
	game_load_map_e(&cub3d()->game, &cub3d()->window, cub3d()->curr_map);
	fte_assert();
	mlx_loop_hook(cub3d()->window.display, loop, NULL);
	mlx_hook(cub3d()->window.win, 3, 2, key_up_handler, NULL);
	mlx_hook(cub3d()->window.win, 2, 3, key_down_handler, NULL);
	mlx_hook(cub3d()->window.win, 6, 1L << 0, mouse_motion_handler, NULL);
	mlx_hook(cub3d()->window.win, 17, 1L << 0, exit_game, NULL);
	mlx_loop(cub3d()->window.display);
	cub3d_exit(0);
}
