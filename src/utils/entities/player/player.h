/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:09:30 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/08 16:06:14 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "../entities.h"
# include <cub3d.h>

typedef struct s_dda_ray
{
	double		length;
	double		angle;
	t_coords	ray_dir;
	t_coords	delta_dist;
	t_coords	side_dist;
	t_coords	map_pos;
	t_coords	step;
	int			side;
	double		wall_x;
	t_entity	*hit_entity;
	t_direction	direction_of_hit_on_entity;
}				t_dda_ray;

typedef struct s_raycast
{
	double		length;
	t_entity	*hit_entity;
	double		x_of_hit_in_entity;
	t_direction	direction_of_hit_on_entity;
}				t_raycast;

void			draw_line(t_ftm_image *canvas, t_coords start, t_coords end,
					unsigned int color);
t_raycast		send_ray(t_game *game, t_coords coords);

#endif