/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:45:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/15 19:57:36 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "targets.h"

t_wall_target	wall_target(t_game *game, t_character *character)
{
    t_coords	coords;
    t_raycast	ray;
    double		angle_adjustment;
    int			i;

    coords = character->billboard.entity.coords;
	i = -1;
    while (++i < TARGETS_RAYS)
    {
        angle_adjustment = (i - (TARGETS_RAYS - 1) / 2.0)
			* (TARGETS_FOV / (TARGETS_RAYS - 1));
        ray = ft_dda_raycast((t_dda_raycast_config){
            (void ***)game->walls, game->map->size,
			(t_coords){coords.x, coords.y,
				ft_normalize_angle(coords.yaw + angle_adjustment)},
				(t_entity *)character});
        if (ray.hit && ((t_entity *)ray.hit)->targetable &&
            ray.distance <= TARGETS_MAX_DIST && i == TARGETS_RAYS / 2)
			return ((t_wall_target){(t_entity *)ray.hit, ray.hit_direction});
    }
    return ((t_wall_target){NULL, 0});
}
