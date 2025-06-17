/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/17 14:35:16 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	load_placeholder_sprite_e(t_ftm_window *window, t_sprite *placeholder)
{
	t_list	*list;
	t_ftm_image	*image;

	fte_set(NULL);
	list = NULL;
	image = ftm_image_from_file(window, PLACEHOLDER_IMAGE_PATH);
	if (!image)
		return (fte_set("load placeholder sprite"));
	ft_list_add(&list, image, ftm_free_image);
	init_sprite(placeholder, list, PLACEHOLDER_SPRITE_UPDATE_DELAY);
}

int	main(int argc, char **argv)
{

	(void)argc;
	fte_storage()->exit = cub3d_exit;
	fte_assert();
	ftm_create_window_e(&cub3d()->window, (t_size){W_WIDTH, W_HEIGHT}, W_TITLE);
	fte_assert();
	load_placeholder_sprite_e(&cub3d()->window, &cub3d()->placeholder);
	fte_assert();
	cub3d()->curr_map = parse_map_e(argv[1]);
	fte_assert();
	fta_init_e();
	game_load_map_e(&cub3d()->game, &cub3d()->window, cub3d()->curr_map);
	fte_assert();
	game_start(&cub3d()->game, &cub3d()->window);
	cub3d_exit(0);
}
