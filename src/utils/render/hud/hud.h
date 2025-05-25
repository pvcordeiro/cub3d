/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:04:15 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/25 02:29:06 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

# include "../render.h"

void	render_debug(t_game *game, t_ftm_image *canvas);
void	render_action(t_game *game, t_ftm_image *canvas);

#endif