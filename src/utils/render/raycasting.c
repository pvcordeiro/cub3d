/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:41 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/06 20:33:59 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

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

static t_ftm_pitc_config	get_pitc_config(int i, t_size *ray_size, t_image *image, t_ray *ray)
{
	return ((t_ftm_pitc_config){
			(t_coords){i * ray_size->width, (W_HEIGHT - ray_size->height) / 2, 0, 0},
			true,
			(t_coords){(int)(ray->x_of_hit_in_entity * image->size.width), 0, 0, 0}, 
			(t_coords){(int)(ray->x_of_hit_in_entity * image->size.width) + 1, image->size.height, 0, 0},
			true,
			*ray_size,
			&ray_size->height,
			pixel_modifier
		});
}

void	render_raycasting_mega(t_game *game, t_image *canvas)
{
	t_player		*player;
	t_size			ray_size;
	t_sprite		*hit_entity_sprite;
	t_image			*hit_entity_image;
	int				i;
	double			angle_diff;

	i = -1;
	player = game->player->private;
	ray_size.width = W_WIDTH / PLAYER_RAYS;
	while (++i < PLAYER_RAYS)
	{
		hit_entity_sprite = &cub3d()->master_sprites.placeholder;
		if (player->rays[i].hit_entity && get_entity_sprite(player->rays[i].hit_entity, player->rays[i].direction_of_hit_on_entity))
			hit_entity_sprite = get_entity_sprite(player->rays[i].hit_entity, player->rays[i].direction_of_hit_on_entity);
		hit_entity_image = get_sprite_image(hit_entity_sprite);
		if (!hit_entity_image)
			continue ;
		angle_diff = player->rays[i].angle - game->player->coords.yaw;
		angle_diff = ft_normalize_angle(angle_diff) * (PI / 180.0);
		ray_size.height = W_HEIGHT / (fmax(player->rays[i].length, 0.5) * cos(angle_diff));
		ray_size.height = fmin(ray_size.height, W_HEIGHT * 3);
		ftm_put_image_to_canvas(canvas, hit_entity_image, get_pitc_config(i, &ray_size, hit_entity_image, &player->rays[i]));
	}
}
