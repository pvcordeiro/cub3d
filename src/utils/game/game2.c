/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:20:04 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/25 19:09:09 by afpachec         ###   ########.fr       */
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
	char	*path;

	if (!paths_str)
		return (NULL);
	paths = ft_split(paths_str, ":");
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = paths[i];
		if (paths[i][0] == '*')
			path = paths[i] + 1;
		if (!ft_strequal(path, "NULL")
			&& !ft_str_endswith(path, ".xpm")
			&& !ft_is_file(path))
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
	char		*path;
	int			i;
	bool		transparency;

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
			transparency = paths[i][0] == '*';
			if (transparency)
				path = ft_strdup(paths[i] + 1);
			else
				path = ft_strdup(paths[i]);
			if (!ft_strequal(path, "NULL"))
			{
				image = ftm_image_from_file(window, path, transparency);
				if (!image)
				{
					printf("Error loading sprite image: %s\n", path);
					return (free(path), fte_set(ERROR_LOAD_SPRITE));
				}
				ft_list_add(&((t_sprite *)ft_hashmap_get_value(game->sprites,
							curr->key))->images, image, ftm_free_image);
			}
			free(path);
		}
	}
	set_sprite_configs(game);
}
