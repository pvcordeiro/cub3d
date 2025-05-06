/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:06:36 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 20:36:10 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	game_load_map_e(t_game *game, t_map *map)
{
	game->map = map;
	create_entities_e(game);
	if (ft_has_error())
	{
		game->map = NULL;
		return ;
	}
}