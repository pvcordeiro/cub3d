/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/14 16:46:16 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	wall_frame(t_entity *entity)
{
	(void)entity;
}

static void	free_wall(void *wall)
{
	free(wall);
}

static void	*hashmap_get_with_identifier(t_hashmap *hashmap, char identifier, char *rest)
{
	char	*key;
	void	*data;

	key = ft_strdup(rest);
	if (identifier != '1')
		key = (free(key), ft_strf("%c_%s", identifier, rest));
	data = ft_hashmap_get_value(hashmap, key);
	return (free(key), data);
}

static double	hashmap_get_with_identifier_double(t_hashmap *hashmap, char identifier, char *rest)
{
	char	*data;

	data = hashmap_get_with_identifier(hashmap, identifier, rest);
	if (!data)
		return (0);
	return (ft_atof(data));
}

t_wall	*wall_new(char identifier, t_game *game)
{
	t_wall	*wall;

	wall = ft_calloc(1, sizeof(t_wall));
	if (!wall)
		return (NULL);
	wall->base.type = ENTITY_WALL;
	wall->base.frame = wall_frame;
	wall->base.free = free_wall;
	wall->base.hard = true;
	wall->base.block = true;
	wall->north_sprite = hashmap_get_with_identifier(game->sprites, identifier, "NO");
	wall->south_sprite = hashmap_get_with_identifier(game->sprites, identifier, "SO");
	wall->west_sprite = hashmap_get_with_identifier(game->sprites, identifier, "WE");
	wall->east_sprite = hashmap_get_with_identifier(game->sprites, identifier, "EA");
	wall->north_depth = hashmap_get_with_identifier_double(game->sprites, identifier, "NO_DEPTH");
	wall->south_depth = hashmap_get_with_identifier_double(game->sprites, identifier, "SO_DEPTH");
	wall->west_depth = hashmap_get_with_identifier_double(game->sprites, identifier, "WE_DEPTH");
	wall->east_depth = hashmap_get_with_identifier_double(game->sprites, identifier, "EA_DEPTH");
	return (wall);
}
