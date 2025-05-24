/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:45:35 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/24 15:02:02 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walls.h"

static t_coords	get_coords(t_ray *ray)
{
	t_coords	coords;

	coords = ray->hit_coords;
	if (ray->hit_direction == WEST || ray->hit_direction == EAST)
		coords.y += ray->hit_x;
	else if (ray->hit_direction == NORTH || ray->hit_direction == SOUTH)
		coords.x += ray->hit_x;
	if (ray->hit_direction == EAST)
		coords.x += 1.0;
	else if (ray->hit_direction == SOUTH)
		coords.y += 1.0;
	return (coords);
}

static void	draw_ray(t_draw_ray_config draw_ray_config)
{
	t_ray		ray;
	t_coords	coords;

	coords = draw_ray_config.coords;
	coords.yaw = draw_ray_config.yaw;
	ray = send_ray(draw_ray_config.game, coords,
			draw_ray_config.ignored_entity);
	if (!ray.hit_entity)
		return ;
	ray.distance += draw_ray_config.previous_distance;
	if (ray.hit_entity->transparent)
	{
		draw_ray_config.coords = get_coords(&ray);
		draw_ray_config.ignored_entity = ray.hit_entity;
		draw_ray_config.previous_distance = ray.distance;
		draw_ray(draw_ray_config);
	}
	draw_ray_line(draw_ray_config.canvas, draw_ray_config.camera,
		ray, draw_ray_config.i);
	if (draw_ray_config.i == draw_ray_config.camera->rays / 2)
	{
		draw_ray_config.camera->entity->target_entity = ray.hit_entity;
		draw_ray_config.camera->entity
			->target_entity_direction = ray.hit_direction;
	}
}

double	fix_ray_step(double	i, t_draw_ray_config drc)
{
	double	half_rays;
	double	dist_to_proj;
	double	angle_step;

	half_rays = drc.camera->rays * 0.5;
	dist_to_proj = half_rays / tan(ft_radians(drc.camera->fov) * 0.5);
	angle_step = atan((i - half_rays) / dist_to_proj);
	return (angle_step);
}

static void	thread_render_rays(void *data)
{
	t_thread_render_rays_data	*trrd;
	t_draw_ray_config			drc;
	unsigned int				i;
	double						angle_step;

	trrd = data;
	i = trrd->start;
	drc = (t_draw_ray_config){trrd->canvas, trrd->camera, trrd->game,
		trrd->camera->entity->coords, trrd->camera->entity, 0, 0, 0};
	while (i < trrd->end)
	{
		drc.i = i;
		angle_step = fix_ray_step((double)i, drc);
		drc.yaw = ft_normalize_angle(drc.camera->entity->coords.yaw + ft_degrees(angle_step));
		draw_ray(drc);
		++i;
	}
}

void	render_walls(t_game *game, t_ftm_image *canvas, t_camera *camera)
{
	static t_thread_render_rays_data	trrd[CAMERA_THREADS];
	unsigned int						i;
	unsigned int						index_scaler;

	i = -1;
	index_scaler = (camera->rays / CAMERA_THREADS);
	while (++i < CAMERA_THREADS)
	{
		if (!trrd[i].canvas)
		{
			trrd[i].canvas = canvas;
			trrd[i].camera = camera;
			trrd[i].game = game;
		}
		trrd[i].start = index_scaler * i;
		trrd[i].end = index_scaler * (i + 1);
		game->camera_threads[i]->routine = thread_render_rays;
		game->camera_threads[i]->data = &trrd[i];
		ftt_thread_run(game->camera_threads[i]);
	}
	i = -1;
	while (++i < CAMERA_THREADS)
		ftt_thread_wait(game->camera_threads[i]);
}
