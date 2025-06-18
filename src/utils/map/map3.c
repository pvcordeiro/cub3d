/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:52:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/18 14:51:36 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static bool	identifier_already_defined(t_identifiers *identifiers, char *identifier)
{
	return (ft_list_any(identifiers->wall, (void *)ft_strequal, identifier)
		|| ft_list_any(identifiers->player, (void *)ft_strequal, identifier)
		|| ft_list_any(identifiers->door, (void *)ft_strequal, identifier)
		|| ft_list_any(identifiers->air, (void *)ft_strequal, identifier)
		|| ft_list_any(identifiers->billboard, (void *)ft_strequal, identifier)
		|| ft_list_any(identifiers->item, (void *)ft_strequal, identifier)
		|| ft_list_any(identifiers->collectible, (void *)ft_strequal, identifier)
		|| ft_list_any(identifiers->drop, (void *)ft_strequal, identifier));
}

static void	add_identifier_e(t_identifiers *identifiers, char *identifier, char *type)
{
	fte_set(NULL);
	if (ft_strequal(type, "WALL"))
		ft_list_add(&identifiers->wall, ft_strdup(identifier), free);
	else if (ft_strequal(type, "PLAYER"))
		ft_list_add(&identifiers->player, ft_strdup(identifier), free);
	else if (ft_strequal(type, "DOOR"))
		ft_list_add(&identifiers->door, ft_strdup(identifier), free);
	else if (ft_strequal(type, "BILLBOARD"))
		ft_list_add(&identifiers->billboard, ft_strdup(identifier), free);
	else if (ft_strequal(type, "ITEM"))
		ft_list_add(&identifiers->item, ft_strdup(identifier), free);
	else if (ft_strequal(type, "COLLECTIBLE"))
		ft_list_add(&identifiers->collectible, ft_strdup(identifier), free);
	else if (ft_strequal(type, "DROP"))
		ft_list_add(&identifiers->drop, ft_strdup(identifier), free);
	else if (ft_strequal(type, "WEAPON"))
		ft_list_add(&identifiers->weapon, ft_strdup(identifier), free);
	else if (ft_strequal(type, "CHARACTER"))
		ft_list_add(&identifiers->character, ft_strdup(identifier), free);
	else
		fte_set("invalid identifier type");
}

static void add_default_identifiers(t_identifiers *identifiers)
{
	int	i;

	i = -1;
	while (DEFAULT_AIR_TYPES[++i])
		ft_list_add(&identifiers->air, ft_strndup(&DEFAULT_AIR_TYPES[i], 1), free);
	i = -1;
	while (DEFAULT_WALL_TYPES[++i])
		ft_list_add(&identifiers->wall, ft_strndup(&DEFAULT_WALL_TYPES[i], 1), free);
	i = -1;
	while (DEFAULT_PLAYER_TYPES[++i])
		ft_list_add(&identifiers->player, ft_strndup(&DEFAULT_PLAYER_TYPES[i], 1), free);
}

void	parse_identifiers_e(t_map *map)
{
	char		*identifier;
	t_element	*el;
	t_element	*curr;

	add_default_identifiers(&map->identifiers);
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
		if (identifier_already_defined(&map->identifiers, identifier))
			return (fte_set("duplicate type identifier %s", identifier), free(identifier));
		add_identifier_e(&map->identifiers, identifier, curr->value);
		if (free(identifier), fte_flagged())
			return ;
	}
}
