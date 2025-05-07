/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:04:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/07 17:25:56 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <cub3d.h>

t_entity	*entity_player_new(char direction);
t_entity	*entity_new(t_entity_type type, void *private);
t_entity	*entity_wall_new(t_game *game);

#endif