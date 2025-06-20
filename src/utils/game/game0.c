/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:27:08 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/19 14:37:03 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	clear_game(void *data)
{
	t_game	*game;

	game = data;
	if (!game)
		return ;
	ft_list_destroy(&game->entities);
	ft_hashmap_destroy(game->sprites);
	kill_threads(game);
	ft_hashmap_destroy(game->fonts);
	ft_hashmap_destroy(game->sounds);
	ft_list_destroy(&game->hud.stats.states_list);
	ft_strvfree((void *)game->walls);
	free(game->billboards);
	ft_bzero(game, sizeof(t_game));
}

void	free_game(void *game)
{
	if (!game)
		return ;
	clear_game(game);
	free(game);
}

static void	init_hashmaps_e(t_game *game)
{
	fte_set(NULL);
	game->sprites = ft_hashmap_new();
	if (!game->sprites)
		return (fte_set("init sprites"));
	game->sounds = ft_hashmap_new();
	if (!game->sounds)
		return (fte_set("init sounds"));
	game->fonts = ft_hashmap_new();
	if (!game->fonts)
		return (fte_set("init sounds"));
	game->sprites_3d = ft_hashmap_new();
	if (!game->fonts)
		return (fte_set("init sprites 3d"));
}

void	game_load_map_e(t_game *game, t_ftm_window *window, t_map *map)
{
	fte_set(NULL);
	game->map = map;
	init_hashmaps_e(game);
	if (fte_flagged())
		return (clear_game(game));
	init_sprites_e(window, game);
	if (fte_flagged())
		return (clear_game(game));
	init_sprites_3d(game);
	init_enviroment_e(game);
	if (fte_flagged())
		return (clear_game(game));
	init_minimap(window, game);
	init_sounds_e(game);
	if (fte_flagged())
		return (clear_game(game));
	init_entities_e(game, window);
	if (fte_flagged())
		return (clear_game(game));
	init_fonts_e(window, game);
	if (fte_flagged())
		return (clear_game(game));
	init_font_e(window, game);
	if (fte_flagged())
		return (clear_game(game));
	init_walls_e(game);
	if (fte_flagged())
		return (clear_game(game));
	insert_door_frames(game);
	init_billboards_e(game);
	if (fte_flagged())
		return (clear_game(game));
	init_hud(game);
	init_window(window, game);
	init_fps(game);
	init_threads_e(game);
	if (fte_flagged())
		return (clear_game(game));
}

void	game_start(t_game *game, t_ftm_window *window)
{
	window->loop_hook = loop;
	window->key_hook = key_hook;
	window->exit_hook = cub3d_exit;
	window->mouse_hook = mouse_hook;
	fta_play(ft_hashmap_get_value(game->sounds, "BACKGROUND"));
	ftm_window_loop(window);
}
