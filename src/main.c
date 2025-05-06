/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:45:49 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	exit_game(void)
{
	cub3d_exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	ft_error_storage()->exit = cub3d_exit;
	parse_map_e(&cub3d()->map, argc, argv);
	ft_error_assert();
	ftm_create_window_e(&cub3d()->window, (t_size){W_WIDTH, W_HEIGHT}, W_TITLE);
	ft_error_assert();
	load_master_sprites_e(&cub3d()->window, &cub3d()->master_sprites, cub3d()->map.types);
	ft_error_assert();
	create_entities_e(&cub3d()->map);
	ft_error_assert();
	mlx_loop_hook(cub3d()->window.display, loop, NULL);
	mlx_hook(cub3d()->window.win, 3, 2, key_up_handler, NULL);
	mlx_hook(cub3d()->window.win, 2, 3, key_down_handler, NULL);
	mlx_hook(cub3d()->window.win, 17, 1L << 0, exit_game, NULL);
	mlx_loop(cub3d()->window.display);
	cub3d_exit(0);
}
