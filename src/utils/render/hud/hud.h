/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:04:15 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/28 17:49:32 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "../render.h"

void	render_debug(t_game *game, t_ftm_image *canvas);
void	render_action(t_game *game, t_ftm_image *canvas);
void	render_stats(t_game *game, t_ftm_image *canvas);
void	render_minimap(t_game *game, t_ftm_image *canvas);

#endif