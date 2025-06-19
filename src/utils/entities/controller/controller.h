/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:31:30 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/18 23:23:04 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_H
# define CONTROLLER_H

# include "../entities.h"

typedef struct s_player_keys
{
	int	walking_forward;
	int	walking_backward;
	int	walking_left;
	int	walking_right;
	int	looking_left;
	int	looking_right;
	int	action;
	int	sprinting;
	int	move_inventory_index;
	int	item_use;
}	t_player_keys;

void	init_player_controller(t_entity *entity);
void	init_ai_dumb_controller(t_entity *entity);
void	init_enemy_controller(t_entity *entity);
void	moviment_frame(t_entity *entity, double delta_time);
void    targets_frame(t_character *character, double fov);

#endif
