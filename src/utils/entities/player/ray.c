/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:05:46 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/03 18:51:49 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

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
			{
				printf("entity: {x: %f, y: %f}; ray: x: {%f y: %f}\n", curr_entity->coords.x, curr_entity->coords.y, coords.x, coords.y);
				return (curr_entity);
			}
		curr = curr->next;
	}
	return (NULL);
}

double	send_ray(t_map *map, t_entity *player, t_coords coords)
{
	t_coords	ray_dir;
	double		length;
	double		step;

	ray_dir.x = cos(ft_normalize_angle(coords.yaw - 90) * PI / 180.0);
	ray_dir.y = sin(ft_normalize_angle(coords.yaw - 90) * PI / 180.0);
	step = 0.01;
	length = 0.0;
	while (length < PLAYER_RAYS_MAX_LENGTH)
	{
		coords.x += ray_dir.x * step;
		coords.y += ray_dir.y * step;
		length += step;
		if (hits_something(map, player, coords))
			return (length);
	}
	return (length);
}
