/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 13:13:31 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

void	key_hook(t_ftm_key_hook_values key_hook_values)
{
	call_entity_keys(cub3d()->game.entities, key_hook_values);
	if (key_hook_values.key == XK_Escape)
		cub3d_exit(0);
	if (key_hook_values.key == XK_F1 && key_hook_values.down)
		ftm_window_toggle_fullscreen(&cub3d()->window, (t_size){W_WIDTH, W_HEIGHT});
}
