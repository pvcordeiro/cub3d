/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/27 19:00:40 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elevator.h"

void	elevator_frame(t_game *game, t_entity *entity, double delta_time)
{
	wall_frame(game, entity, delta_time);
}

void	clear_elevator(void *data)
{
	clear_wall(data);
}

void	elevator_action(t_entity *entity, t_character *actioner)
{
	t_elevator	*elevator;

	wall_action(entity, actioner);
	elevator = (t_elevator *)entity;
	cub3d()->prev_map = cub3d()->curr_map;
	cub3d()->curr_map = parse_map_e(elevator->map_path);
	if (fte_flagged())
	{
		cub3d()->curr_map = cub3d()->prev_map;
		printf("Error loading map: %s\n", fte_storage()->msg);
	}
}

void	elevator_shot(t_entity *shooted, t_character *shooter)
{
	wall_shot(shooted, shooter);
}
