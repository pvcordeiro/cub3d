/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:59:45 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 16:32:26 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static unsigned	pixel_modifier(void *data, unsigned pixel)
{
	t_rgba			rgba;
	double			gradient;

	gradient = fmin(((t_size *)data)->height / (W_HEIGHT / 1.5), 1.0);
	rgba.r = ((pixel >> 16) & 0xEE) * gradient;
	rgba.g = ((pixel >> 8) & 0xEE) * gradient;
	rgba.b = (pixel & 0xEE) * gradient;
	rgba.a = (pixel >> 24);
	return ((rgba.a << 24) | (rgba.r << 16) | (rgba.g << 8) | rgba.b);
}

static t_ftm_pitc_config	get_pitc_config(int i, t_size *ray_size, t_ftm_image *image, t_ray *ray)
{
	double	x_of_hit;

	x_of_hit = ray->hit_x;
	if (ray->hit_direction == NORTH || ray->hit_direction == EAST)
		x_of_hit = 1.0 - ray->hit_x;
	return ((t_ftm_pitc_config){
			(t_coords){i * ray_size->width, (W_HEIGHT - ray_size->height) / 2, 0},
			true,
			(t_coords){(int)(x_of_hit * image->size.width), 0, 0}, 
			(t_coords){(int)(x_of_hit * image->size.width) + 1, image->size.height, 0},
			true,
			*ray_size,
			ray_size,
			pixel_modifier
		});
}

void	draw_ray_line(t_ftm_image *canvas, t_camera *camera, t_ray ray, int i)
{
	t_size				ray_size;
	t_ftm_image			*hit_entity_image;

	ray_size.width = canvas->size.width / camera->rays;
	hit_entity_image = get_sprite_image(get_entity_sprite(ray.hit_entity, ray.hit_direction));
	if (!hit_entity_image)
		return ;
	ray_size.height = canvas->size.height / (fmax(ray.distance, 0.1) * cos(ft_normalize_angle((camera->entity->coords.yaw - (PLAYER_FOV / 2)) - camera->entity->coords.yaw) * (PI / 180.0)));
	ray_size.height = fmin(ray_size.height, canvas->size.height * 3);
	ftm_put_image_to_canvas(canvas, hit_entity_image, get_pitc_config(i, &ray_size, hit_entity_image, &ray));
}
