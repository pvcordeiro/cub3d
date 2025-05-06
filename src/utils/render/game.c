/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:49:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 19:56:00 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	render_ceiling_and_floor(t_map *map, t_image *canvas)
{
    ftm_draw_rectangle(canvas, (t_coords){0, 0, 0, 0}, 
        (t_size){W_WIDTH, W_HEIGHT / 2}, map->ceiling_color, map->ceiling_color);
    ftm_draw_rectangle(canvas, (t_coords){0, W_HEIGHT / 2, 0, 0}, 
        (t_size){W_WIDTH, W_HEIGHT / 2}, map->floor_color, map->floor_color);
}
