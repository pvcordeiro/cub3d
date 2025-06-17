/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:31:30 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/16 16:59:10 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_H
# define CONTROLLER_H

# include "../entities.h"

void	init_player_controller(t_entity *entity);
void	init_ai_dumb_controller(t_entity *entity);
void	init_enemy_controller(t_entity *entity);
void	moviment_frame(t_entity *entity, double delta_time);
void    targets_frame(t_character *character, double fov);

#endif
