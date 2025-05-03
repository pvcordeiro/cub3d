/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:09:30 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/03 12:45:33 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <cub3d.h>
# include "../entities.h"

void	draw_line(t_image *canvas, t_coords start, t_coords end, 
	unsigned int color);
double	send_ray(t_map *map, t_entity *player, t_coords coords);

#endif