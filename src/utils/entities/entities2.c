/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:25:11 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/29 00:08:21 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"

t_entity	*entity_new(t_entity_type type, void *private)
{
	t_entity	*entity;

	entity = ft_calloc(1, sizeof(t_entity));
	if (!entity)
		return (NULL);
	entity->type = type;
	entity->private = private;
	return (entity);
}

double normalize_angle(double angle) {
    angle = fmod(angle, 360.0);
    if (angle < 0)
        angle += 360.0;
    return angle;
}
