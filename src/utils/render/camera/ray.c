/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:05:46 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/20 15:39:54 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static double	calculate_wall_dist(t_dda_ray *data, t_coords coords)
{
	double	wall_dist;

	if (data->side == 0)
	{
		wall_dist = (data->map_pos.x - coords.x + (1 - data->step.x) / 2)
		/ data->ray_dir.x;
		if (data->step.x > 0)
        	data->direction_of_hit_on_entity = WEST;
		else
			data->direction_of_hit_on_entity = EAST;
	}
	else
	{
		wall_dist = (data->map_pos.y - coords.y + (1 - data->step.y) / 2)
			/ data->ray_dir.y;
		if (data->step.y > 0)
			data->direction_of_hit_on_entity = NORTH;
		else
			data->direction_of_hit_on_entity = SOUTH;
	}
	return (wall_dist);
}

static t_entity	*hit_entity(t_game *game, t_dda_ray *data, t_coords coords)
{
	t_entity	*entity;
	t_list		*curr;

	curr = game->entities;
	while (curr)
	{
		entity = curr->data;
		curr = curr->next;
		if (!entity->block
			|| (int)entity->coords.x != (int)coords.x
			|| (int)entity->coords.y != (int)coords.y)
			continue ;
		data->length = calculate_wall_dist(data, coords);
		if (data->direction_of_hit_on_entity == data->direction_to_ignore && entity == data->entity_to_ignore)
			continue ;
		return (entity);
	}
	return (NULL);
}

static void	init_dda_ray_data(t_dda_ray *data, t_coords coords)
{
	double	angle_rad;

	angle_rad = ft_normalize_angle(coords.yaw) * PI / 180.0;
	data->ray_dir.x = cos(angle_rad);
	data->ray_dir.y = sin(angle_rad);
	data->map_pos.x = (int)coords.x;
	data->map_pos.y = (int)coords.y;
	if (data->ray_dir.x == 0)
		data->delta_dist.x = 1e30;
	else
		data->delta_dist.x = fabs(1 / data->ray_dir.x);
	if (data->ray_dir.y == 0)
		data->delta_dist.y = 1e30;
	else
		data->delta_dist.y = fabs(1 / data->ray_dir.y);
}

static void	set_step_and_side_dist(t_dda_ray *data, t_coords coords)
{
	if (data->ray_dir.x < 0)
	{
		data->step.x = -1;
		data->side_dist.x = (coords.x - data->map_pos.x) * data->delta_dist.x;
	}
	else
	{
		data->step.x = 1;
		data->side_dist.x = (data->map_pos.x + 1.0 - coords.x)
			* data->delta_dist.x;
	}
	if (data->ray_dir.y < 0)
	{
		data->step.y = -1;
		data->side_dist.y = (coords.y - data->map_pos.y) * data->delta_dist.y;
	}
	else
	{
		data->step.y = 1;
		data->side_dist.y = (data->map_pos.y + 1.0 - coords.y)
			* data->delta_dist.y;
	}
}

static double	perform_dda(t_dda_ray *data, t_game *game)
{
	t_coords	check_pos;

	while (1)
	{
		if (data->side_dist.x < data->side_dist.y)
		{
			data->side_dist.x += data->delta_dist.x;
			data->map_pos.x += data->step.x;
			data->side = 0;
		}
		else
		{
			data->side_dist.y += data->delta_dist.y;
			data->map_pos.y += data->step.y;
			data->side = 1;
		}
		check_pos = (t_coords){data->map_pos.x, data->map_pos.y, 0};
		if (hit_entity(game, data, check_pos))
			break ;
		if (data->map_pos.x < 0 || data->map_pos.x >= game->map->size.width
			|| data->map_pos.y < 0 || data->map_pos.y >= game->map->size.height)
			return (PLAYER_RAYS_NO_HIT_LENGTH);
	}
	return (0);
}

static void	calculate_wall_hit(t_dda_ray *data, t_coords coords, t_entity *entity_hit)
{
	data->hit_entity = entity_hit;
	if (data->side == 0)
		data->wall_x = coords.y + data->length * data->ray_dir.y;
	else
		data->wall_x = coords.x + data->length * data->ray_dir.x;
	data->wall_x -= floor(data->wall_x);
}

t_raycast	send_ray(t_game *game, t_coords coords, t_entity *entity_to_ignore, t_direction direction_to_ignore)
{
	t_dda_ray	data;
	double		result;
	t_entity	*entity_hit;

	init_dda_ray_data(&data, coords);
	data.entity_to_ignore = entity_to_ignore;
	data.direction_to_ignore = direction_to_ignore;
	set_step_and_side_dist(&data, coords);
	result = perform_dda(&data, game);
	if (result > 0)
		return ((t_raycast){result, NULL, 0, 0, {0, 0, 0}});
	entity_hit = hit_entity(game, &data, (t_coords){data.map_pos.x, data.map_pos.y, 0});
	data.length = calculate_wall_dist(&data, coords);
	calculate_wall_hit(&data, coords, entity_hit);
	return ((t_raycast){data.length, entity_hit, data.wall_x, data.direction_of_hit_on_entity, data.map_pos});
}