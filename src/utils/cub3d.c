/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 03:17:29 by afpachec         ###   ########.fr       */
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

static bool	alloc_walls(t_game *game)
{
	int	i;

	game->walls = ft_calloc(game->map->size.height, sizeof(t_entity **));
	if (!game->walls)
		return (false);
	i = -1;
	while (++i < game->map->size.height)
	{
		game->walls[i] = ft_calloc(game->map->size.width, sizeof(t_entity *));
		if (game->walls[i])
			continue ;
        while (--i >= 0)
            free(game->walls[i]);
        free(game->walls);
		game->walls = NULL;
		return (false);
	}
	return (true);
}

void	update_walls_matrix(t_game *game)
{
	t_entity	*entity;
	t_list		*curr;

	if (!game)
		return ;
	if (!game->walls && !alloc_walls(game))
		return ;
	curr = game->entities;
	while (curr)
	{
		entity = curr->data;
		curr = curr->next;
		if (!entity->wall || entity->coords.x < 0
			|| entity->coords.x >= game->map->size.width || entity->coords.y < 0
			|| entity->coords.y >= game->map->size.height)
			continue ;
		game->walls[(int)entity->coords.y][(int)entity->coords.x] = entity;
	}
}

static bool	is_billboard(t_entity *entity, void *param)
{
	(void)param;
	return (entity && entity->billboard);
}

void	update_billboards_vec(t_game *game)
{
    t_entity	*entity;
    t_list		*curr;
    size_t		i;
    size_t		billboard_count;

    if (!game || !game->entities)
        return ;
    billboard_count = ft_list_count(game->entities, (void *)is_billboard, NULL);
    if (!game->billboards
		|| billboard_count != ft_strvlen((void *)game->billboards))
    {
        free(game->billboards);
        game->billboards = ft_calloc(billboard_count + 1, sizeof(t_entity *));
        if (!game->billboards)
            return ;
    }
	ft_bzero(game->billboards, sizeof(t_entity *) * (billboard_count + 1));
    curr = game->entities;
    i = -1;
    while (curr)
    {
        entity = curr->data;
        curr = curr->next;
        if (!entity->billboard)
            continue ;
        game->billboards[++i] = entity;
    }
}

t_type_creator	get_type_creator(t_hashmap *ids, char identifier)
{
	if (ft_list_any(identifiers_get(ids, "ITEM"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)item_new);
	if (ft_list_any(identifiers_get(ids, "COLLECTIBLE"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)collectible_new);
	if (ft_list_any(identifiers_get(ids, "WEAPON"), (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)weapon_new);
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
	free_game(cub3d()->game);
	cub3d()->game = NULL;
	free_map(cub3d()->curr_map);
	free_map(cub3d()->prev_map);
	cub3d()->curr_map = NULL;
	cub3d()->prev_map = NULL;
	clear_sprite(&cub3d()->placeholder);
	ftm_clear_window(&cub3d()->window);
	fta_destroy();
	pthread_mutex_destroy(&cub3d()->game_mutex);
	exit(code);
}
