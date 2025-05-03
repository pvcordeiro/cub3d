/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:41 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/03 22:58:33 by paude-so         ###   ########.fr       */
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

	player = map->player->private;
	ray_width = W_WIDTH / PLAYER_RAYS;
	ray_size.width = ray_width;
	i = -1;
	while (++i < PLAYER_RAYS)
	{
		angle_diff = player->rays[i].angle - map->player->coords.yaw;
		angle_diff = ft_normalize_angle(angle_diff) * (PI / 180.0);
		ray_size.height = W_HEIGHT / (player->rays[i].length * cos(angle_diff));
		color = 0x000000 + (0x111111 * (ray_size.height / (W_HEIGHT / 16)));
		if (color > 0xFFFFFF)
			color = 0xFFFFFF;
		draw_rectangle(canvas, (t_coords){i * ray_width, (W_HEIGHT - ray_size.height) / 2, 0, 0}, ray_size, color, color); 
	}
}
