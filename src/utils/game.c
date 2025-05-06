/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:06:36 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 20:43:18 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static unsigned convert_color_to_hex(char *str)
{
	unsigned color;
	char **strs;

	strs = ft_split(str, ",");
	color = ft_atoi(strs[0]);
	color *= 0x000100;
	color += ft_atoi(strs[1]);
	color *= 0x000100;
	color += ft_atoi(strs[2]);
	ft_strvfree(strs);
	return (color);
}

void	init_enviroment(t_game *game)
{
	game->environment.ceiling_color = convert_color_to_hex(ft_hashmap_get_value(game->map->types, "C"));
	game->environment.floor_color = convert_color_to_hex(ft_hashmap_get_value(game->map->types, "F"));
}

void	game_load_map_e(t_game *game, t_map *map)
{
	game->map = map;
	create_entities_e(game);
	if (ft_has_error())
	{
		game->map = NULL;
		return ;
	}
	init_enviroment(game);
}
