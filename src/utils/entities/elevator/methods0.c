/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 03:05:04 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elevator.h"

void	elevator_frame(t_game *game, t_entity *entity, double delta_time)
{
	t_elevator		*elevator;

	wall_frame(game, entity, delta_time);
	elevator = (t_elevator *)entity;
	(void)elevator;
}

void	clear_elevator(void *elevator)
{
	clear_wall(elevator);
}

void	elevator_action(t_entity *entity, t_character *actioner)
{
	t_elevator	*elevator;

	wall_action(entity, actioner);
	elevator = (t_elevator *)entity;
	cub3d()->prev_map = cub3d()->curr_map;
	cub3d()->curr_map = parse_map_e(elevator->map_path);
	if (fte_flagged())
		cub3d()->curr_map = cub3d()->prev_map;
}

void	elevator_shot(t_entity *shooted, t_character *shooter)
{
	wall_shot(shooted, shooter);
}
