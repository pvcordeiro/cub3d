/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:05:46 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/04 11:21:02 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static t_entity	*hits_something(t_map *map, t_entity *entity, t_coords coords)
{
	int			x;
	int			y;
	t_entity	*hit_entity;

	x = (int)coords.x;
	y = (int)coords.y;
	if (x < 0 || x >= map->size.width || y < 0 || y >= map->size.height)
		return (NULL);
	hit_entity = map->entity_grid[y][x];
	if (hit_entity && hit_entity != entity && hit_entity->hard)
		return (hit_entity);
	return (NULL);
}

static void	init_ray_data(t_ray *data, t_coords coords)
{
	double	angle_rad;

	angle_rad = ft_normalize_angle(coords.yaw - 90) * PI / 180.0;
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

static void	set_step_and_side_dist(t_ray *data, t_coords coords)
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

static double	perform_dda(t_ray *data, t_map *map, t_entity *player)
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
		check_pos = (t_coords){data->map_pos.x, data->map_pos.y, 0, 0};
		if (hits_something(map, player, check_pos))
			break ;
		if (data->map_pos.x < 0 || data->map_pos.x >= map->size.width
			|| data->map_pos.y < 0 || data->map_pos.y >= map->size.height)
			return (PLAYER_RAYS_MAX_LENGTH);
	}
	return (0);
}

static double	calculate_wall_dist(t_ray *data, t_coords coords)
{
	double	wall_dist;

	if (data->side == 0)
		wall_dist = (data->map_pos.x - coords.x + (1 - data->step.x) / 2)
			/ data->ray_dir.x;
	else
		wall_dist = (data->map_pos.y - coords.y + (1 - data->step.y) / 2)
			/ data->ray_dir.y;
	return (wall_dist);
}

static void	calculate_wall_hit(t_ray *data, t_coords coords, t_entity *hit_entity)
{
	data->hit_entity = hit_entity;
	if (data->side == 0)
		data->wall_x = coords.y + data->length * data->ray_dir.y;
	else
		data->wall_x = coords.x + data->length * data->ray_dir.x;
	data->wall_x -= floor(data->wall_x);
}

double	send_ray(t_map *map, t_entity *player, t_coords coords)
{
	t_ray		data;
	double		result;
	t_entity	*hit_entity;

	init_ray_data(&data, coords);
	set_step_and_side_dist(&data, coords);
	result = perform_dda(&data, map, player);
	if (result > 0)
		return (result);
	data.length = calculate_wall_dist(&data, coords);
	hit_entity = hits_something(map, player, (t_coords){data.map_pos.x, data.map_pos.y, 0, 0});
	calculate_wall_hit(&data, coords, hit_entity);
	return (data.length);
}
