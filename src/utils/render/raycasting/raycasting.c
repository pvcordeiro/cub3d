/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:41 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/03 20:28:52 by paude-so         ###   ########.fr       */
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

	player = map->player->private;
	ray_width = W_WIDTH / PLAYER_RAYS;
	ray_size.width = ray_width;
	i = -1;
	while (++i < PLAYER_RAYS)
	{
		ray_size.height = W_HEIGHT / player->rays[i].length;
		if (ray_size.height / (W_HEIGHT / 4) > 2)
			color = 0xFFFFFF;
		else if (ray_size.height / (W_HEIGHT / 4) > 1)
			color = 0xDDDDDD;
		else
			color = 0xAAAAAA;
		draw_rectangle(canvas, (t_coords){i * ray_width, (W_HEIGHT - ray_size.height) / 2, 0, 0}, ray_size, color, color); 
	}
}
