/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 03:05:19 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "billboard.h"

void	billboard_frame(t_game *game, t_entity *entity, double delta_time)
{
	entity_frame(game, entity, delta_time);
}

void	clear_billboard(void *billboard)
{
	clear_entity(billboard);
}

void	billboard_action(t_entity *entity, t_character *actioner)
{
	entity_action(entity, actioner);
}

void	billboard_shot(t_entity *shooted, t_character *shooter)
{
	entity_shot(shooted, shooter);
}
