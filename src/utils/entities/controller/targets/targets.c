/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:42:39 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/17 14:29:50 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "targets.h"

double	signed_angle_to(t_coords from, t_coords to)
{
    double angle_to = ft_degrees(atan2(to.y - from.y, to.x - from.x));
    double diff = angle_to - from.yaw;

    while (diff > 180.0)
        diff -= 360.0;
    while (diff < -180.0)
        diff += 360.0;
    return diff;
}

void	targets_frame(t_character *character, double fov)
{
	t_wall_target	wall_tar_data;
	t_entity		*bill_tar_entity;

	if (!character)
		return;
	character->target_entity = NULL;
	wall_tar_data = wall_target(&cub3d()->game, character, fov);
	if (wall_tar_data.entity)
		character->target_entity = wall_tar_data.entity;
	bill_tar_entity = billboard_target(&cub3d()->game, (t_entity *)character, fov);
	if (bill_tar_entity)
		character->target_entity = bill_tar_entity;
}
