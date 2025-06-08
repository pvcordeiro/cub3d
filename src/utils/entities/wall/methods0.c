/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 13:03:54 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

void	wall_frame(t_entity *entity, double delta_time)
{
	entity_frame(entity, delta_time);
}

void	clear_wall(void *wall)
{
	clear_entity(wall);
}

void	wall_action(t_entity *entity, t_entity *actioner)
{
	entity_action(entity, actioner);
}

void	wall_shot(t_entity *shooted, t_entity *shooter)
{
	entity_action(shooted, shooter);
}
