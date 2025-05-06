/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:06:36 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 22:55:26 by afpachec         ###   ########.fr       */
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

void	init_minimap(t_game *game, t_window *window)
{
	t_minimap	*minimap;

	minimap = &game->minimap;
	minimap->width_multiplier = MINIMAP_WIDTH_MULTIPLIER;
	minimap->height_multiplier = MINIMAP_HEIGHT_MULTIPLIER;
	minimap->coords = (t_coords){10, window->size.height - (window->size.height * minimap->height_multiplier) - 10, 0, 0};
	minimap->size = (t_size){window->size.width * game->minimap.width_multiplier, window->size.height * game->minimap.height_multiplier};
	minimap->background_color = 0xCC555555;
	minimap->border_color = 0xAAAAAA;
	minimap->wall_color = 0xAAAAAA;
	minimap->player_color = 0xFF0000;
	minimap->player_ray_color = 0x114C00B0;
}

void	game_load_map_e(t_game *game, t_window *window, t_map *map)
{
	game->map = map;
	create_entities_e(game);
	if (ft_has_error())
	{
		game->map = NULL;
		return ;
	}
	init_enviroment(game);
	init_minimap(game, window);
}

void	free_game(void *game)
{
	if (!game)
		return ;
	ft_list_destroy(&((t_game *)game)->entities);
	ft_strvfree((char **)(((t_game *)game)->entity_grid));
	ft_bzero(game, sizeof(t_game));
}
