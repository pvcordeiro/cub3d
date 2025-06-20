/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:52:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 10:54:08 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static bool	identifier_already_defined(t_hashmap *identifiers, char *identifier)
{
	t_element	*el;
	t_list		*curr;

	el = *identifiers->table;
	while (el)
	{
		curr = el->value;
		el = el->next;
		if (curr && ft_list_any(*((t_list **)curr->data), (void *)ft_strequal, identifier))
			return (true);
	}
	return (false);
}

static void	id_list_free(t_list **id_list)
{
	ft_list_destroy(id_list);
	free(id_list);
}

static void	add_identifier(t_hashmap *identifiers, char *identifier, char *type)
{
	t_list	**ids;

	ids = (t_list **)ft_hashmap_get_value(identifiers, type);
	if (!ids)
	{
		ids = malloc(sizeof(t_list *));
		if (!ids)
			return ;
		*ids = NULL;
		ft_hashmap_set(identifiers, type, ids, (void *)id_list_free);
		ids = (t_list **)ft_hashmap_get_value(identifiers, type);
	}
	ft_list_add(ids, ft_strdup(identifier), free);
}

static void add_default_identifiers(t_hashmap *identifiers)
{
	char	*id_str;
	int		i;

	i = -1;
	while (DEFAULT_AIR_TYPES[++i])
	{
		id_str = ft_strndup(&DEFAULT_AIR_TYPES[i], 1);
		(add_identifier(identifiers, "AIR", id_str), free(id_str));
	}
	i = -1;
	while (DEFAULT_WALL_TYPES[++i])
	{
		id_str = ft_strndup(&DEFAULT_WALL_TYPES[i], 1);
		(add_identifier(identifiers, "WALL", id_str), free(id_str));
	}
	i = -1;
	while (DEFAULT_PLAYER_TYPES[++i])
	{
		id_str = ft_strndup(&DEFAULT_PLAYER_TYPES[i], 1);
		(add_identifier(identifiers, "PLAYER", id_str), free(id_str));
	}
}

void	parse_identifiers_e(t_map *map)
{
	char		*identifier;
	t_element	*el;
	t_element	*curr;

	fte_set(NULL);
	map->identifiers = ft_hashmap_new();
	if (!map->identifiers)
		return (fte_set("Identifier Hashmap Error (its so over)"));
	add_default_identifiers(map->identifiers);
	el = *map->types->table;
	while (el)
	{
		curr = el;
		el = el->next;
		if (!ft_str_endswith(curr->key, "_TYPE"))
			continue ;
		identifier = ft_strndup(curr->key, ft_strlen(curr->key) - 5);
		if (!identifier || !*identifier)
			return (free(identifier), fte_set("empty type identifier"));
		if (identifier_already_defined(map->identifiers, identifier))
			return (fte_set("duplicate type identifier %s", identifier), free(identifier));
		add_identifier(map->identifiers, identifier, curr->value);
		if (free(identifier), fte_flagged())
			return ;
	}
}
