/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 10:51:26 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*hashmap_get_with_identifier(t_game *game, t_hashmap *hashmap, char identifier, char *rest)
{
	char	*key;
	void	*data;

	key = ft_strdup(rest);
	if (!rest)
		key = (free(key), ft_strndup(&identifier, 1));
	else if (ft_list_any(ft_hashmap_get_value(game->map->identifiers, "PLAYER"),
		(void *)ft_str_equal_char_ptr, &identifier))
		key = (free(key), ft_strdup(rest));
	else if (identifier)
		key = (free(key), ft_strf("%c_%s", identifier, rest));
	data = ft_hashmap_get_value(hashmap, key);
	return (free(key), data);
}

t_type_creator	get_type_creator(t_hashmap *ids, char identifier)
{
	if (ft_list_any(ft_hashmap_get_value(ids, "ITEM"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)item_new);
	if (ft_list_any(ft_hashmap_get_value(ids, "COLLECTIBLE"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)collectible_new);
	if (ft_list_any(ft_hashmap_get_value(ids, "WEAPON"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)weapon_new);
	if (ft_list_any(ft_hashmap_get_value(ids, "AIR"), (void *)ft_str_equal_char_ptr, &identifier))
		return (NULL);
	if (ft_list_any(ft_hashmap_get_value(ids, "WALL"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)wall_new);
	if (ft_list_any(ft_hashmap_get_value(ids, "PLAYER"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)player_new);
	if (ft_list_any(ft_hashmap_get_value(ids, "DOOR"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)door_new_e);
	if (ft_list_any(ft_hashmap_get_value(ids, "BILLBOARD"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)billboard_new);
	if (ft_list_any(ft_hashmap_get_value(ids, "DROP"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)drop_new);
	if (ft_list_any(ft_hashmap_get_value(ids, "CHARACTER"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)character_new);
	if (ft_list_any(ft_hashmap_get_value(ids, "ELEVATOR"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)elevator_new);
	return (NULL);
}

t_cub3d	*cub3d(void)
{
	static t_cub3d	singleton;

	return (&singleton);
}

void	cub3d_exit(int code)
{
	free_map(cub3d()->curr_map);
	clear_game(&cub3d()->game);
	clear_sprite(&cub3d()->placeholder);
	ftm_clear_window(&cub3d()->window);
	fta_destroy();
	exit(code);
}
