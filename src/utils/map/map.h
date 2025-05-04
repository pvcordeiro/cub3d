/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:04:16 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/04 13:15:06 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <cub3d.h>

void	process_raw_map_e(t_map *map);
void	set_map_size(t_map *map);
bool	is_map_char(char c);
void	set_map_colors(t_map *map);

#endif