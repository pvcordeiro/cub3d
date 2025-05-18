/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:16:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/18 10:43:14 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_enviroment_e(t_game *game)
{
	char	*ceiling;
	char	*flooring;

	fte_set(ERROR_NO_ERROR);
	ceiling = ft_hashmap_get_value(game->map->types, "C");
	flooring = ft_hashmap_get_value(game->map->types, "F");
	if (!ceiling || !flooring)
		return (fte_set(ERROR_CEILING_OR_FLOORING_UNDEFINED));
	game->environment.ceiling_color = ft_rgb_to_unsigned(ceiling, ",");
	game->environment.floor_color = ft_rgb_to_unsigned(flooring, ",");
}

void	init_minimap(t_ftm_window *window, t_game *game)
{
	t_minimap	*minimap;

	minimap = &game->minimap;
	minimap->width_multiplier = MINIMAP_WIDTH_MULTIPLIER;
	minimap->height_multiplier = MINIMAP_HEIGHT_MULTIPLIER;
	minimap->coords = (t_coords){10, window->size.height
		- (window->size.height * minimap->height_multiplier) - 10, 0};
	minimap->size = (t_size){window->size.width
		* game->minimap.width_multiplier, window->size.height
		* game->minimap.height_multiplier};
	minimap->background_color = 0xCC555555;
	minimap->border_color = 0xFFAAAAAA;
	minimap->wall_color = 0xFFAAAAAA;
	minimap->player_color = 0xFFFF0000;
	minimap->player_ray_color = 0xFF880088;
	minimap->player_middle_ray_color = 0xFFFF0000;
	minimap->entity_color = 0xFF888888;
	minimap->door_color = 0xFF8888DD;
}

void	init_window(t_ftm_window *window, t_game *game)
{
	char	*value;

	value = ft_hashmap_get_value(game->map->types, "MOUSE");
	window->using_mouse = ft_strequal(value, "TRUE");
}
