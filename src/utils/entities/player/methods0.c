/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 01:22:08 by afpachec         ###   ########.fr       */
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
