/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 12:10:15 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_list	*identifiers_get(t_hashmap *ids, char *type)
{
	t_list	**id;

	id = ft_hashmap_get_value(ids, type);
	if (id)
		return (*id);
	return (NULL);
}

void	*hashmap_get_with_identifier(t_game *game, t_hashmap *hashmap, char identifier, char *rest)
{
	char	*key;
	void	*data;

	key = ft_strdup(rest);
	if (!rest)
		key = (free(key), ft_strndup(&identifier, 1));
	else if (ft_list_any(identifiers_get(game->map->identifiers, "PLAYER"),
		(void *)ft_str_equal_char_ptr, &identifier))
		key = (free(key), ft_strdup(rest));
	else if (identifier)
		key = (free(key), ft_strf("%c_%s", identifier, rest));
	data = ft_hashmap_get_value(hashmap, key);
	return (free(key), data);
}

t_type_creator	get_type_creator(t_hashmap *ids, char identifier)
{
	if (ft_list_any(identifiers_get(ids, "ITEM"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)item_new);
	if (ft_list_any(identifiers_get(ids, "COLLECTIBLE"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)collectible_new);
	if (ft_list_any(identifiers_get(ids, "WEAPON"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)weapon_new);
	if (ft_list_any(identifiers_get(ids, "AIR"), (void *)ft_str_equal_char_ptr, &identifier))
		return (NULL);
	if (ft_list_any(identifiers_get(ids, "WALL"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)wall_new);
	if (ft_list_any(identifiers_get(ids, "PLAYER"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)player_new);
	if (ft_list_any(identifiers_get(ids, "DOOR"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)door_new_e);
	if (ft_list_any(identifiers_get(ids, "BILLBOARD"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)billboard_new);
	if (ft_list_any(identifiers_get(ids, "DROP"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)drop_new);
	if (ft_list_any(identifiers_get(ids, "CHARACTER"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)character_new);
	if (ft_list_any(identifiers_get(ids, "ELEVATOR"), (void *)ft_str_equal_char_ptr, &identifier))
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
