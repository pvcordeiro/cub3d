/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 18:47:24 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	player_frame(t_entity *entity, double delta_time)
{
	billboard_frame(entity, delta_time);
}

void	clear_player(void *player)
{
	clear_billboard(player);
}

void	player_action(t_entity *entity, t_entity *actioner)
{
	billboard_action(entity, actioner);
}

void	player_shot(t_entity *shooted, t_entity *shooter)
{
	billboard_shot(shooted, shooter);
}
