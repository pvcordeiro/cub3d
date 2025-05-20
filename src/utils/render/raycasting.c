/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:41 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/20 15:39:44 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// static unsigned	pixel_modifier(void *data, unsigned pixel)
// {
// 	t_ray			*ray;
// 	t_rgba			rgba;
// 	double			gradient;

// 	ray = data;
// 	gradient = fmin(ray->_height / (W_HEIGHT / 1.5), 1.0);
// 	rgba.r = ((pixel >> 16) & 0xEE) * gradient;
// 	rgba.g = ((pixel >> 8) & 0xEE) * gradient;
// 	rgba.b = (pixel & 0xEE) * gradient;
// 	rgba.a = (pixel >> 24);
// 	return ((rgba.a << 24) | (rgba.r << 16) | (rgba.g << 8) | rgba.b);
// }

// static t_ftm_pitc_config	get_pitc_config(int i, t_size *ray_size, t_ftm_image *image, t_ray *ray)
// {
// 	double	x_of_hit;

// 	x_of_hit = ray->x_of_hit_in_entity;
// 	if (ray->direction_of_hit_on_entity == NORTH || ray->direction_of_hit_on_entity == EAST)
// 		x_of_hit = 1.0 - ray->x_of_hit_in_entity;
// 	ray->_height = ray_size->height;
// 	return ((t_ftm_pitc_config){
// 			(t_coords){i * ray_size->width, (W_HEIGHT - ray_size->height) / 2, 0},
// 			true,
// 			(t_coords){(int)(x_of_hit * image->size.width), 0, 0}, 
// 			(t_coords){(int)(x_of_hit * image->size.width) + 1, image->size.height, 0},
// 			true,
// 			*ray_size,
// 			ray,
// 			pixel_modifier
// 		});
// }

// void	render_raycasting_slice(void *data)
// {
// 	t_raycasting_slice	*slice;
// 	t_ray				ray;
// 	t_size				ray_size;
// 	t_ftm_image			*hit_entity_image;
// 	int					i;
// 	int					j;

// 	slice = data;
// 	ray_size.width = W_WIDTH / PLAYER_RAYS;
// 	i = slice->starting_index - 1;
// 	while (++i < slice->ending_index)
// 	{
// 		j = PLAYER_RAY_SUBRAYS;
// 		while (j--)
// 		{
// 			ray = slice->player->rays[i][j];
// 			if (!ray.hit_entity)
// 				continue ;
// 			hit_entity_image = get_sprite_image(get_entity_sprite(ray.hit_entity, ray.direction_of_hit_on_entity));
// 			if (!hit_entity_image)
// 				continue ;
// 			ray_size.height = W_HEIGHT / (fmax(ray.length, 0.1) * cos(ft_normalize_angle(ray.angle - slice->player->base.coords.yaw) * (PI / 180.0)));
// 			ray_size.height = fmin(ray_size.height, W_HEIGHT * 3);
// 			ftm_put_image_to_canvas(slice->canvas, hit_entity_image, get_pitc_config(i, &ray_size, hit_entity_image, &ray));
// 		}
// 	}
// }

// void	render_raycasting_mega(t_game *game, t_ftm_image *canvas)
// {
// 	static t_raycasting_slice	raycasting_slices[RENDERING_THREADS];
// 	t_ftt_thread				*curr_thread;
// 	int	i;

// 	i = -1;
// 	while (++i < RENDERING_THREADS)
// 	{
// 		curr_thread = game->rendering_threads[i];
// 		raycasting_slices[i].canvas = canvas;
// 		raycasting_slices[i].player = game->player;
// 		raycasting_slices[i].starting_index = i * (PLAYER_RAYS / RENDERING_THREADS);
// 		raycasting_slices[i].ending_index = (i + 1) * (PLAYER_RAYS / RENDERING_THREADS);
// 		curr_thread->routine = render_raycasting_slice;
// 		curr_thread->data = &raycasting_slices[i];
// 		ftt_thread_run(curr_thread);
// 	}
// 	i = -1;
// 	while (++i < RENDERING_THREADS)
// 		ftt_thread_wait(game->rendering_threads[i]);
// }
