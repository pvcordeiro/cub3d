/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:05:46 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/17 02:21:01 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

double	ft_distance(t_coords a, t_coords b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

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
            && coords.x <= (curr_entity->coords.x + 1.0)
            && coords.y >= curr_entity->coords.y
            && coords.y <= (curr_entity->coords.y + 1.0))
            return (curr_entity);
    }
    return (NULL);
}

static t_direction	get_hit_direction(bool last_move_was_x, t_coords hit_pos, t_entity *entity)
{
    if (last_move_was_x)
    {
        if(hit_pos.x > entity->coords.x + 0.5)
			return (EAST);
		return (WEST);
    }
	if (hit_pos.y > entity->coords.y + 0.5)
		return (SOUTH);
	return (NORTH);
}

static double	get_x_or_y_of_hit(t_coords hit, t_entity *entity, t_direction direction)
{
	if (!entity)
		return (0);
	if (direction == NORTH || direction == SOUTH)
		return (hit.x - entity->coords.x);
	else if (direction == EAST || direction == WEST)
		return (hit.y - entity->coords.y);
	return (0);
}

double	get_distance(t_coords coords, t_entity *entity, t_direction hit_direction, double x)
{
	t_coords	entity_coords;

	entity_coords = entity->coords;
	if (hit_direction == SOUTH)
		entity_coords.y += 1.0;
	if (hit_direction == EAST)
		entity_coords.x += 1.0;
	if (hit_direction == WEST || hit_direction == EAST)
		entity_coords.y += x;
	if (hit_direction == NORTH || hit_direction == SOUTH)
		entity_coords.x += x;
	return (ft_distance(coords, entity_coords));
}

t_raycast	send_ray(t_game *game, t_coords coords)
{
	t_entity	*entity;
	t_coords	ray_coords;
	t_direction	hit_direction;
	double		step_x;
	double		step_y;
	bool		last_move_was_x;
	int			travelled;
	double		xhit;

	step_x = cos(coords.yaw * FT_MLX_UTILS_PI / 180.0) * 0.1;
	step_y = sin(coords.yaw * FT_MLX_UTILS_PI / 180.0) * 0.1;
	ray_coords = coords;
	last_move_was_x = false;
	travelled = 0;
	while (travelled < 200)
	{
		ray_coords.y += step_y;
		last_move_was_x = false;
		entity = get_hit_entity(game, ray_coords);
		if (entity)
			break;
		ray_coords.x += step_x;
		last_move_was_x = true;
		entity = get_hit_entity(game, ray_coords);
		if (entity)
			break;
		++travelled;
	}
	if (!entity)
		return ((t_raycast){0, NULL, 0, 0});
	hit_direction = get_hit_direction(last_move_was_x, ray_coords, entity);
	xhit = get_x_or_y_of_hit(ray_coords, entity, hit_direction);
	return ((t_raycast){get_distance(coords, entity, hit_direction, xhit), entity,
		xhit, hit_direction});
}
