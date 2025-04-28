/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:49:46 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/28 23:25:20 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

static void	create_entity(t_list **list, char c)
{
	if (ft_isspace(c) || c == '0')
		return ;
	else if (c == '1')
		create_wall(list);
	else if (ft_strchr("NSEW", c))
		create_player(list, c);
}

void	create_entities(t_map *map, t_list **list)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
			create_entity(list, map->map[i][++j]);
	}
}
