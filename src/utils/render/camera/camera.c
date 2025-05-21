/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:59 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 23:05:51 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

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
	if ((unsigned int)draw_ray_config.i == draw_ray_config.camera->rays / 2)
	{
		draw_ray_config.camera->entity->target_entity = ray.hit_entity;
		draw_ray_config.camera->entity
			->target_entity_direction = ray.hit_direction;
	}
}

static void	thread_render_rays(void *data)
{
	t_thread_render_rays_data	*trrd;
	t_draw_ray_config			drc;
	unsigned int				i;

	trrd = data;
	i = -1;
	drc = (t_draw_ray_config){trrd->canvas, trrd->camera, trrd->game,
		trrd->camera->entity->coords, trrd->camera->entity, 0, 0, 0};
	while (++i < trrd->camera->rays)
	{
		drc.i = i;
		drc.yaw = ft_normalize_angle(((trrd->camera->entity->coords.yaw
						- (trrd->camera->fov / 2)))
				+ ((trrd->camera->fov / trrd->camera->rays) * i));
		draw_ray(drc);
	}
}

void	render_camera(t_game *game, t_ftm_image *canvas, t_camera *camera)
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
