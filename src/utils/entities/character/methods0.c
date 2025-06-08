/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 16:10:50 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

void	character_frame(t_entity *entity, double delta_time)
{
	billboard_frame(entity, delta_time);
}

void	clear_character(void *character)
{
	clear_billboard(character);
}

void	character_action(t_entity *entity, t_entity *actioner)
{
	billboard_action(entity, actioner);
}

void	character_shot(t_entity *shooted, t_entity *shooter)
{
	billboard_shot(shooted, shooter);
}
