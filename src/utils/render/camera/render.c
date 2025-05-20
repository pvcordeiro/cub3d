/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:59:45 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 21:39:51 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static unsigned int	pixel_modifier(void *data, unsigned int pixel)
{
	t_pixel_modifier_data	*pmd;
	t_rgba					rgba;
	double					gradient;

	pmd = data;
	gradient = fmin(pmd->ray_size->height
			/ (pmd->canvas->size.width / 1.5), 1.0);
	rgba.r = ((pixel >> 16) & 0xEE) * gradient;
	rgba.g = ((pixel >> 8) & 0xEE) * gradient;
	rgba.b = (pixel & 0xEE) * gradient;
	rgba.a = (pixel >> 24);
	return ((rgba.a << 24) | (rgba.r << 16) | (rgba.g << 8) | rgba.b);
}

static t_ftm_pitc_config	get_pitc_config(t_get_pitc_config_config gpcc)
{
	double	x_of_hit;

	x_of_hit = gpcc.ray->hit_x;
	if (gpcc.ray->hit_direction == NORTH || gpcc.ray->hit_direction == EAST)
		x_of_hit = 1.0 - gpcc.ray->hit_x;
	return ((t_ftm_pitc_config){
		(t_coords){gpcc.i * gpcc.ray_size->width,
		(gpcc.canvas->size.height - gpcc.ray_size->height) / 2, 0},
		true,
		(t_coords){(int)(x_of_hit * gpcc.image->size.width), 0, 0},
		(t_coords){(int)(x_of_hit * gpcc.image->size.width) + 1,
		gpcc.image->size.height, 0},
		true,
		*gpcc.ray_size,
		gpcc.pixel_modifier_data,
		pixel_modifier
	});
}

void	draw_ray_line(t_ftm_image *canvas, t_camera *camera, t_ray ray, int i)
{
	t_size					ray_size;
	t_ftm_image				*hit_entity_image;
	t_pixel_modifier_data	pixel_modifier_data;

	ray_size.width = canvas->size.width / camera->rays;
	hit_entity_image = get_sprite_image(get_entity_sprite(ray.hit_entity,
				ray.hit_direction));
	if (!hit_entity_image)
		return ;
	ray_size.height = canvas->size.height / (fmax(ray.distance, 0.1)
			* cos(ft_normalize_angle((camera->entity->coords.yaw
						- (camera->fov / 2))
					- camera->entity->coords.yaw) * (PI / 180.0)));
	ray_size.height = fmin(ray_size.height, canvas->size.height * 3);
	pixel_modifier_data = (t_pixel_modifier_data){canvas, &ray_size};
	ftm_put_image_to_canvas(canvas, hit_entity_image,
		get_pitc_config((t_get_pitc_config_config){i, &ray_size,
			hit_entity_image, &ray, canvas, &pixel_modifier_data}));
}
