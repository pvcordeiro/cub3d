/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:04:15 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/20 21:59:54 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "../hud.h"

int	render_debug_str(t_ftm_font *font, t_ftm_image *canvas, char *str, t_coords coords);

void	set_fps(t_game *game);
void	render_debug_fps_strs(t_game *game, t_ftm_image *canvas, t_coords coords);
void	set_target(t_game *game);
void	set_player(t_game *game);
void	render_debug_player_strs(t_game *game, t_ftm_image *canvas, t_coords coords);
void	set_entities(t_game *game);

#endif