/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:41:28 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/18 17:54:05 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlay.h"

void	render_image_info(t_game *game)
{
	char	*str;
	
	if (!game->player->looking_at_entity)
		return ;
	str = ftm_image_to_str(get_sprite_image(get_entity_sprite(game->player->looking_at_entity, game->player->looking_at_entity_direction)));
	if (str)
		mlx_string_put(cub3d()->window.display, cub3d()->window.win, 38, 65, 0xFFFFFFFF, str);
	free(str);
}
