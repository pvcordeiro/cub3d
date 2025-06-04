/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:04:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 23:04:11 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <cub3d.h>

void	init_controller(t_entity *entity, const char *type);
void	free_entity(void *entity);
bool	add_item_to_inventory(t_entity *entity, t_item *item);

// Entity
void	init_entity(t_game *game, t_ftm_window *window, t_entity *entity, char identifier);
void	entity_frame(t_entity *entity, double delta_time);
void	clear_entity(void *entity);
void	free_entity(void *entity);
void	entity_action(t_entity *entity, t_entity *actioner);

// Billboard
void	init_billboard(t_game *game, t_ftm_window *window, t_billboard *billboard, char identifier);
void	billboard_frame(t_entity *entity, double delta_time);
void	clear_billboard(void *billboard);
void	billboard_action(t_entity *entity, t_entity *actioner);

// Wall
void	init_wall(t_game *game, t_ftm_window *window, t_wall *wall, char identifier);
void	wall_frame(t_entity *entity, double delta_time);
void	clear_wall(void *wall);
void	wall_action(t_entity *entity, t_entity *actioner);

// Door
void	init_door_e(t_game *game, t_ftm_window *window, t_door *door, char identifier);
void	door_frame(t_entity *entity, double delta_time);
void	clear_door(void *door);
void	door_action(t_entity *entity, t_entity *actioner);

// Player
void	init_player(t_game *game, t_ftm_window *window, t_player *player, char identifier);
void	player_frame(t_entity *entity, double delta_time);
void	clear_player(void *player);
void	player_action(t_entity *entity, t_entity *actioner);

// Drop
void	init_drop(t_game *game, t_ftm_window *window, t_drop *drop, char identifier);
void	drop_frame(t_entity *entity, double delta_time);
void	clear_drop(void *drop);
void	drop_action(t_entity *entity, t_entity *actioner);


#endif