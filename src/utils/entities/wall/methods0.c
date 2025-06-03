/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 01:22:19 by afpachec         ###   ########.fr       */
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
