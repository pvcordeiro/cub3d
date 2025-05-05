/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:13:29 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/04 19:15:24 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_ceiling_and_floor(t_map *map, t_image *canvas)
{
    draw_rectangle(canvas, (t_coords){0, 0, 0, 0}, 
        (t_size){W_WIDTH, W_HEIGHT / 2}, map->ceiling_color, map->ceiling_color);
    draw_rectangle(canvas, (t_coords){0, W_HEIGHT / 2, 0, 0}, 
        (t_size){W_WIDTH, W_HEIGHT / 2}, map->floor_color, map->floor_color);
}
