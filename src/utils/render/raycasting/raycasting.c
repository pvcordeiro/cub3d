/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:41 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/04 00:54:21 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	render_raycasting_mega(t_map *map, t_image *canvas)
{
	t_player		*player;
	t_size			ray_size;
	int				ray_width;
	int				i;
	unsigned int	color;
	double			angle_diff;
	double			gradient;

    draw_rectangle(canvas, (t_coords){0, 0, 0, 0}, 
        (t_size){W_WIDTH, W_HEIGHT / 2}, 0x4682B4, 0x4682B4);
    draw_rectangle(canvas, (t_coords){0, W_HEIGHT / 2, 0, 0}, 
        (t_size){W_WIDTH, W_HEIGHT / 2}, 0x5D4037, 0x5D4037);
	player = map->player->private;
	ray_width = W_WIDTH / PLAYER_RAYS;
	ray_size.width = ray_width;
	i = -1;
	while (++i < PLAYER_RAYS)
	{
		angle_diff = player->rays[i].angle - map->player->coords.yaw;
		angle_diff = ft_normalize_angle(angle_diff) * (PI / 180.0);
		ray_size.height = W_HEIGHT / (fmax(player->rays[i].length, 0.1) * cos(angle_diff));
		ray_size.height = fmin(ray_size.height, W_HEIGHT * 3);
		gradient = fmin(ray_size.height / (W_HEIGHT / 2.0), 1.0);
        int r = (int)(gradient * 255);
        int g = (int)(gradient * 255);
        int b = (int)(gradient * 255);
        color = (r << 16) | (g << 8) | b;
		draw_rectangle(canvas, (t_coords){i * ray_width, (W_HEIGHT - ray_size.height) / 2, 0, 0}, ray_size, color, color); 
	}
}
