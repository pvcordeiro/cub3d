/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 01:21:32 by afpachec         ###   ########.fr       */
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
