/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 10:09:11 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elevator.h"

void	elevator_frame(t_entity *entity, double delta_time)
{
	t_elevator		*elevator;

	wall_frame(entity, delta_time);
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
	(void)elevator;
}

void	elevator_shot(t_entity *shooted, t_character *shooter)
{
	wall_shot(shooted, shooter);
}
