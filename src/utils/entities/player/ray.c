/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:50:22 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/01 18:10:10 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_line(void)
{

}

static t_entity	*hits_something(t_map *map, t_entity *entity, t_coords coords)
{
	t_list		*curr;
	t_entity	*curr_entity;

	curr = map->entities;
	while (curr)
	{
		curr_entity = curr->data;
		if (curr_entity != entity
			&& curr_entity->hard
			&& (int)curr_entity->coords.x == (int)coords.x
			&& (int)curr_entity->coords.y == (int)coords.y)
			return (curr_entity);
		curr = curr->next;
	}
	return (NULL);
}

double	get_size_ray(t_map *map, t_coords coords)
{
	t_list		*curr;
	t_entity	*entity;
	double		length;

	length = 0;
	curr = map->entities;
	while (!hits_something(map, cub3d()->player, coords))
	{
		coords
	}
}