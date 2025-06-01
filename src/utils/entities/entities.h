/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:04:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/31 19:33:40 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <cub3d.h>

void	*hashmap_get_with_identifier(t_hashmap *hashmap, char identifier, char *rest);
void	init_entity(t_game *game, t_entity *entity, char identifier);
void	init_billboard(t_game *game, t_billboard *billboard, char identifier);
void	init_enemy(t_game *game, t_enemy *enemy, char identifier);
void	init_wall(t_game *game, t_wall *wall, char identifier);
void	init_door_e(t_game *game, t_door *door, char identifier, t_ftm_window *window);
void	init_controller(t_entity *entity, const char *type);

#endif