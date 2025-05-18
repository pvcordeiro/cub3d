/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:02:15 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/18 17:50:48 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlay.h"

void	render_debug(t_game *game)
{
	render_image_info(game);
	render_fps(game);
	//TODO render_player_pos(game);
}