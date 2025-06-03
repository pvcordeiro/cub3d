/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:20:04 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 17:57:04 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static bool	is_sprite_type(const char *key)
{
	if (!key)
		return (false);
	return (ft_str_endswith(key, "_NO") || ft_str_endswith(key, "_SO")
		|| ft_str_endswith(key, "_WE") || ft_str_endswith(key, "_EA")
		|| ft_strequal(key, "NO") || ft_strequal(key, "SO")
		|| ft_strequal(key, "WE") || ft_strequal(key, "EA")
		|| ft_str_endswith(key, "_SPRITE"));
}

static char	**get_sprite_paths(const char *paths_str)
{
	int		i;
	char	**paths;

	if (!paths_str)
		return (NULL);
	paths = ft_split(paths_str, ":");
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		if (!ft_strequal(paths[i], "NULL")
			&& !ft_str_endswith(paths[i], ".xpm")
			&& !ft_is_file(paths[i]))
			return (ft_strvfree(paths), NULL);
	}
	return (paths);
}

void	init_sprites_e(t_ftm_window *window, t_game *game)
{
	t_sprite	*sprite;
	t_ftm_image	*image;
	t_element	*el;
	t_element	*curr;
	char		**paths;
	int			i;

	fte_set(ERROR_NO_ERROR);
	image = NULL;
	el = *game->map->types->table;
	while (el)
	{
		curr = el;
		el = el->next;
		if (!is_sprite_type((char *)curr->key))
			continue ;
		paths = get_sprite_paths(curr->value);
		if (!paths)
			return (fte_set(ERROR_LOAD_SPRITE));
		sprite = sprite_new(NULL, 0);
		if (!sprite)
			return (ft_strvfree(paths), fte_set(ERROR_LOAD_SPRITE));
		ft_hashmap_set(game->sprites, curr->key, sprite, free_sprite);
		i = -1;
		while (paths[++i])
		{
			if (ft_strequal(paths[i], "NULL"))
				continue ;
			image = ftm_image_from_file(window, paths[i]);
			if (!image)
				return (ft_strvfree(paths), fte_set(ERROR_LOAD_SPRITE));
			ft_list_add(&((t_sprite *)ft_hashmap_get_value(game->sprites,
						curr->key))->images, image, ftm_free_image);
		}
		ft_strvfree(paths);
	}
	set_sprite_configs(game);
}
