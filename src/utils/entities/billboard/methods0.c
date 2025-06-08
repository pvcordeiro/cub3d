/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 18:40:18 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "billboard.h"

void	billboard_frame(t_entity *entity, double delta_time)
{
	entity_frame(entity, delta_time);
}

void	clear_billboard(void *billboard)
{
	clear_entity(billboard);
}

void	billboard_action(t_entity *entity, t_entity *actioner)
{
	entity_action(entity, actioner);
}

void	billboard_shot(t_entity *shooted, t_entity *shooter)
{
	entity_shot(shooted, shooter);
}
