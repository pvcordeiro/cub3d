/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:09:30 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/17 15:20:04 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <cub3d.h>
# include "../entities.h"

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
	t_direction direction_to_ignore;
	t_entity	*entity_to_ignore;
}	t_dda_ray;

typedef struct	s_raycast
{
	double		length;
	t_entity	*hit_entity;
	double		x_of_hit_in_entity;
	t_direction	direction_of_hit_on_entity;
	t_coords	hit_coords;
}	t_raycast;

t_raycast	send_ray(t_game *game, t_coords coords, t_entity *entity_to_ignore, t_direction direction_to_ignore);

#endif