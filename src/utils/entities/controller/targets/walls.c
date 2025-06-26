/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvcordeiro <pvcordeiro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:45:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/26 14:53:33 by pvcordeiro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "targets.h"

t_wall_target	wall_target(t_game *game, t_character *character, double fov)
{
	t_coords	coords;
	t_raycast	ray;
	double		angle_adjustment;
	int			i;
	t_entity	*entity;

	coords = character->billboard.entity.coords;
	i = -1;
	while (++i < TARGETS_RAYS)
	{
		angle_adjustment = (i - (TARGETS_RAYS - 1) / 2.0)
			* (fov / (TARGETS_RAYS - 1));
		ray = ft_dda_raycast((t_dda_raycast_config){
				(void ***)game->walls, game->map->size,
				(t_coords){coords.x, coords.y,
				ft_normalize_angle(coords.yaw + angle_adjustment)},
				(t_entity *)character});
		entity = (t_entity *)ray.hit;
		if (ray.hit && entity->targetable
			&& ray.distance <= TARGETS_MAX_DIST && i == TARGETS_RAYS / 2
			&& (entity->type == ENTITY_DOOR
				&& ray.distance < DOOR_INTERACTION_DISTANCE))
			return ((t_wall_target){entity, ray.hit_direction});
	}
	return ((t_wall_target){NULL, 0});
}
