/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:05:46 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/04 00:22:55 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walls.h"

#define LARGE_DOUBLE 1e30

static void	init_dda_ray_data(t_game *game, t_dda_ray *ray, t_coords coords)
{
	ray->ray_dir.x = ft_cos_degrees(coords.yaw);
	ray->ray_dir.y = ft_sin_degrees(coords.yaw);
	ray->map_pos.x = (int)coords.x;
	ray->map_pos.y = (int)coords.y;
	ray->map_size = game->map->size;
	ray->delta_dist.x = LARGE_DOUBLE;
	if (ray->ray_dir.x)
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = LARGE_DOUBLE;
	if (ray->ray_dir.y)
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
}

static void	set_step_and_side_dist(t_dda_ray *ray, t_coords coords)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (coords.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - coords.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (coords.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - coords.y)
			* ray->delta_dist.y;
	}
}

static t_entity	*perform_dda(t_dda_ray *ray, t_game *game)
{
	t_entity	*hit;

	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
		}
		if (ray->map_pos.x < 0 || ray->map_pos.x >= ray->map_size.width
			|| ray->map_pos.y < 0 || ray->map_pos.y >= ray->map_size.height)
			return (NULL);
		hit = game->walls[(int)ray->map_pos.y][(int)ray->map_pos.x];
		if (hit && hit->active && hit != ray->ignored_entity)
			return (hit);
	}
}

static double	calculate_wall_dist(t_dda_ray *ray, t_coords coords)
{
	double	wall_dist;

	if (ray->side == 0)
	{
		wall_dist = (ray->map_pos.x - coords.x
				+ (1 - ray->step.x) / 2) / ray->ray_dir.x;
		ray->direction_of_hit_on_entity = EAST;
		if (ray->step.x > 0)
			ray->direction_of_hit_on_entity = WEST;
	}
	else
	{
		wall_dist = (ray->map_pos.y - coords.y
				+ (1 - ray->step.y) / 2) / ray->ray_dir.y;
		ray->direction_of_hit_on_entity = SOUTH;
		if (ray->step.y > 0)
			ray->direction_of_hit_on_entity = NORTH;
	}
	return (wall_dist);
}

t_ray	send_ray(t_game *game, t_coords coords, t_entity *ignored_entity)
{
	t_dda_ray	ray;

	init_dda_ray_data(game, &ray, coords);
	ray.ignored_entity = ignored_entity;
	set_step_and_side_dist(&ray, coords);
	ray.hit_entity = perform_dda(&ray, game);
	if (!ray.hit_entity)
		return ((t_ray){PLAYER_RAYS_NO_HIT_LENGTH, coords.yaw,
			NULL, 0, 0, (t_coords){0, 0, 0}});
	ray.length = calculate_wall_dist(&ray, coords);
	if (ray.side == 0)
		ray.wall_x = coords.y + ray.length * ray.ray_dir.y;
	else
		ray.wall_x = coords.x + ray.length * ray.ray_dir.x;
	ray.wall_x -= floor(ray.wall_x);
	return ((t_ray){
		ray.length,
		coords.yaw,
		ray.hit_entity,
		ray.wall_x,
		ray.direction_of_hit_on_entity,
		ray.map_pos
	});
}
