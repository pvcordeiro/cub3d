/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:51:47 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/18 18:35:01 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlay.h"
//TODO notworking
void	render_player_pos(t_game *game)
{
	char		*str;

	str = ft_strf("Player X: %.2f | Y: %.2f | Angle: %.2f", game->player->base.coords.x, game->player->base.coords.y, game->player->base.coords.yaw);
	printf("%s\n", str);
	printf("x %.2f, y %.2f, angle %.2f\n", game->player->base.coords.x, game->player->base.coords.x, game->player->base.coords.yaw);
	if (str)
		mlx_string_put(cub3d()->window.display, cub3d()->window.win, 38, 85, 0xFFFFFFFF, str);
	free(str);
}
