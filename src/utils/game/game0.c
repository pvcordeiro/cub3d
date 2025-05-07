/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:27:08 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 17:47:23 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	clear_game(void *game)
{
	if (!game)
		return ;
	ft_list_destroy(&((t_game *)game)->entities);
	ft_strvfree((char **)(((t_game *)game)->entity_grid));
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

void	game_load_map_e(t_game *game, t_window *window, t_map *map)
{
	game->map = map;
	init_sprites_e(window, game);
	if (ft_has_error())
		return (clear_game(game));
	init_enviroment_e(game);
	if (ft_has_error())
		return (clear_game(game));
	init_minimap(window, game);
	create_entities_e(game);
	if (ft_has_error())
		return (clear_game(game));
}
