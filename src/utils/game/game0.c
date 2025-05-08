/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:27:08 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/08 15:55:10 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	clear_game(void *game)
{
	if (!game)
		return ;
	ft_list_destroy(&((t_game *)game)->entities);
	ft_strvfree((char **)(((t_game *)game)->wall_grid));
	ft_hashmap_destroy(((t_game *)game)->sprites);
	ft_bzero(game, sizeof(t_game));
}

void	free_game(void *game)
{
	if (!game)
		return ;
	clear_game(game);
	free(game);
}

void	game_load_map_e(t_game *game, t_ftm_window *window, t_map *map)
{
	fte_set(ERROR_NO_ERROR);
	game->map = map;
	game->sprites = ft_hashmap_new();
	if (!game->sprites)
		return (fte_set(ERROR_INIT_SPRITES));
	init_sprites_e(window, game);
	if (fte_flagged())
		return (clear_game(game));
	init_enviroment_e(game);
	if (fte_flagged())
		return (clear_game(game));
	init_minimap(window, game);
	init_entities_e(game);
	if (fte_flagged())
		return (clear_game(game));
}
