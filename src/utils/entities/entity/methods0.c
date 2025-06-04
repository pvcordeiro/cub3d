/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 15:44:47 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"

void	entity_frame(t_entity *entity, double delta_time)
{
	if (entity->controller.frame)
		entity->controller.frame(entity, delta_time);
}

void	clear_entity(void *entity)
{
	if (!entity)
		return ;
	free(((t_entity *)entity)->inventory);
}

void	entity_action(t_entity *entity, t_entity *actioner)
{
	((void)entity, (void)actioner);
}
