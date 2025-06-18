/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:04:15 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/18 20:55:07 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "../render.h"

typedef struct s_minimap_data
{
	t_game		*game;
	t_ftm_image	*canvas;
	t_character	*character;
	t_coords	coords;
	t_size		size;
}	t_minimap_data;

void	render_debug(t_game *game, t_ftm_image *canvas, t_character *character);
void	render_action(t_game *game, t_ftm_image *canvas, t_character *character);
void	render_stats(t_game *game, t_ftm_image *canvas, t_character *character);
void	render_minimap(t_game *game, t_ftm_image *canvas, t_character *character);
void	render_hand_item(t_ftm_image *canvas, t_character *character);
void	render_effects(t_ftm_image *canvas, t_character *character);

#endif