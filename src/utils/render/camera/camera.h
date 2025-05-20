/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:40:06 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 15:41:01 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../render.h"

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

#endif
