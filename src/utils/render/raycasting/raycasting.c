/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:41 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/05 01:16:35 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static unsigned	pixel_modifier(void *data, unsigned pixel)
{
	double			gradient;
	int				r;
	int				g;
	int				b;

	gradient = fmin(*(int *)data / (W_HEIGHT / 1.5), 1.0);
	r = ((pixel >> 16) & 0xEE) * gradient;
	g = ((pixel >> 8) & 0xEE) * gradient;
	b = (pixel & 0xEE) * gradient;
	return ((r << 16) | (g << 8) | b);
}

void	render_raycasting_mega(t_map *map, t_image *canvas)
{
	t_player		*player;
	t_size			ray_size;
	t_sprite		*hit_entity_sprite;
	t_image			*hit_entity_image;
	int				ray_width;
	int				i;
	double			angle_diff;

	i = -1;
	player = map->player->private;
	ray_width = W_WIDTH / PLAYER_RAYS;
	ray_size.width = ray_width;
	while (++i < PLAYER_RAYS)
	{
		hit_entity_sprite = &cub3d()->master_sprites.missing;
		if (player->rays[i].hit_entity && player->rays[i].hit_entity->sprite)
			hit_entity_sprite = player->rays[i].hit_entity->sprite;
		hit_entity_image = get_sprite_image(hit_entity_sprite);
		if (!hit_entity_image)
			continue ;
		angle_diff = player->rays[i].angle - map->player->coords.yaw;
		angle_diff = ft_normalize_angle(angle_diff) * (PI / 180.0);
		ray_size.height = W_HEIGHT / (fmax(player->rays[i].length, 0.5) * cos(angle_diff));
		ray_size.height = fmin(ray_size.height, W_HEIGHT * 3);
		render_cropped_image_to_canvas(canvas,
			hit_entity_image,
			(t_render_cropped_image_config){
				(t_coords){i * ray_width, (W_HEIGHT - ray_size.height) / 2, 0, 0},
				(t_coords){(int)(player->rays[i].x_of_hit_in_entity * 64), 0, 0, 0}, 
				(t_coords){(int)(player->rays[i].x_of_hit_in_entity * 64) + 1, 64, 0, 0},
				ray_size,
				&ray_size.height,
				pixel_modifier
			}
		);
	}
}
