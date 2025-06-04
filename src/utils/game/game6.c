/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:30:03 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 01:24:56 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_walls_e(t_game *game)
{
	t_entity	*entity;
	t_list		*curr;
	size_t		i;

	fte_set(NULL);
	game->walls = ft_calloc(game->map->size.height + 1, sizeof(t_entity **));
	if (!game->walls)
		return (fte_set("walls init (outer calloc)"));
	i = -1;
	while (++i < (size_t)game->map->size.height)
	{
		game->walls[i] = ft_calloc(game->map->size.width + 1, sizeof(t_entity *));
		if (!game->walls[i])
			return (fte_set("walls init (inner calloc)"));
	}
	curr = game->entities;
	i = -1;
	while (curr)
	{
		entity = curr->data;
		curr = curr->next;
		if (!entity->wall || entity->coords.x < 0 || entity->coords.x >= game->map->size.width
			|| entity->coords.y < 0 || entity->coords.y >= game->map->size.height)
			continue ;
		game->walls[(int)entity->coords.y][(int)entity->coords.x] = entity;
	}
}

static size_t	count_billboards(t_list *entities)
{
	t_entity	*entity;
	size_t		count;

	count = 0;
	while (entities)
	{
		entity = entities->data;
		if (entity->billboard)
			count++;
		entities = entities->next;
	}
	return (count);
}

void	init_billboards_e(t_game *game)
{
	t_entity	*entity;
	t_list		*curr;
	size_t		i;

	fte_set(NULL);
	game->billboards = ft_calloc(count_billboards(game->entities) + 1, sizeof(t_entity *));
	if (!game->billboards)
		return (fte_set("billboards init"));
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
