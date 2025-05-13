/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:05:46 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/13 14:32:42 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static t_entity	*get_hit_entity(t_game *game, t_coords coords)
{
    t_list		*curr;
    t_entity	*curr_entity;

	curr = game->entities;
    while (curr)
    {
        curr_entity = curr->data;
        curr = curr->next;
        if (curr_entity->block
            && coords.x >= curr_entity->coords.x
            && coords.x <= (curr_entity->coords.x + 0.99999999)
            && coords.y >= curr_entity->coords.y
            && coords.y <= (curr_entity->coords.y + 0.99999999))
            return (curr_entity);
    }
    return (NULL);
}
static int get_hit_direction(double angle, t_coords hit_pos, t_entity *entity)
{
    double rel_x;
    double rel_y;

	if (!entity)
		return (0);
	rel_x = hit_pos.x - entity->coords.x;
	rel_y = hit_pos.y - entity->coords.y;
    if (rel_x < 0.01)
        return (WEST);
    if (rel_x > 0.99)
        return (EAST);
    if (rel_y < 0.01)
        return (NORTH);
    if (rel_y > 0.99)
        return (SOUTH);
    angle = fmod(angle + 360.0, 360.0);
    if (angle >= 315 || angle < 45)
        return (EAST);
    if (angle >= 45 && angle < 135)
        return (SOUTH);
    if (angle >= 135 && angle < 225)
        return (WEST);
    return (NORTH);
}

static double	get_x_or_y_of_hit(t_coords hit, t_entity *entity)
{
	double	rel_x;
	double	rel_y;

	if (!entity)
		return (0);
	rel_x = hit.x - entity->coords.x;
	rel_y = hit.y - entity->coords.y;
	if (rel_x < 0.01)
		return (rel_y);
	if (rel_x > 0.99)
		return (rel_y);
	if (rel_y < 0.01)
		return (rel_x);
	if (rel_y > 0.99)
		return (rel_x);
	return (-1);
}

t_raycast	send_ray(t_game *game, t_coords coords)
{
	t_entity	*entity;
	t_coords	ray_coords;
	double		step_x;
	double		step_y;
	double		travelled;

	step_x = cos(coords.yaw * FT_MLX_UTILS_PI / 180.0) * 0.01;
	step_y = sin(coords.yaw * FT_MLX_UTILS_PI / 180.0) * 0.01;
	ray_coords = coords;
	travelled = 0;
	while (travelled < 200)
	{
		entity = get_hit_entity(game, ray_coords);
		if (entity)
			break;
		ray_coords.x += step_x;
		ray_coords.y += step_y;
		travelled += 0.01;
	}
	return ((t_raycast){ft_distance(coords, ray_coords), entity,
				get_x_or_y_of_hit(ray_coords, entity), get_hit_direction(coords.yaw, ray_coords, entity)});
}
