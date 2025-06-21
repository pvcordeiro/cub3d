/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:27:08 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 13:56:43 by afpachec         ###   ########.fr       */
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
	free_walls(game);
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

t_game	*game_new(t_ftm_window *window, t_map *map)
{
	t_game	*game;

	fte_set(NULL);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (fte_set("game new"), NULL);
	game->map = map;
	init_hashmaps_e(game);
	if (fte_flagged())
		return (free_game(game), NULL);
	init_sprites_e(window, game);
	if (fte_flagged())
		return (free_game(game), NULL);
	init_sprites_3d(game);
	init_enviroment_e(game);
	if (fte_flagged())
		return (free_game(game), NULL);
	init_minimap(window, game);
	init_sounds_e(game);
	if (fte_flagged())
		return (free_game(game), NULL);
	init_entities_e(game, window);
	if (fte_flagged())
		return (free_game(game), NULL);
	init_fonts_e(window, game);
	if (fte_flagged())
		return (free_game(game), NULL);
	init_font_e(window, game);
	if (fte_flagged())
		return (free_game(game), NULL);
	update_walls_matrix(game);
	if (fte_flagged())
		return (free_game(game), NULL);
	insert_door_frames(game);
	update_billboards_vec(game);
	if (fte_flagged())
		return (free_game(game), NULL);
	init_hud(game);
	init_window(window, game);
	init_fps(game);
	init_threads_e(game);
	if (fte_flagged())
		return (free_game(game), NULL);
	game->background_sound = ft_hashmap_get_value(game->sounds, "BACKGROUND");
	return (game);
}

