/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:04:15 by paude-so          #+#    #+#             */
/*   Updated: 2025/06/18 20:02:44 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "../render.h"

void	render_debug(t_game *game, t_ftm_image *canvas);
void	render_action(t_game *game, t_ftm_image *canvas);
void	render_stats(t_game *game, t_ftm_image *canvas);
void	render_minimap(t_game *game, t_ftm_image *canvas);
void	render_hand_item(t_game *game, t_ftm_image *canvas);
void	render_effects(t_game *game, t_ftm_image *canvas);

#endif