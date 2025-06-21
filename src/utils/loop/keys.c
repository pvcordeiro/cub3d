/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:21:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 20:58:45 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop.h"

static void	activate_another_player(t_game *game)
{
	int	i;

	i = -1;
	while (++i < PLAYER_MAX)
	{
		if (!game->players[i])
			return ;
		if (game->players[i]->character.billboard.entity.active)
			continue ;
		game->players[i]->character.billboard.entity.active = true;
		return ;
	}
}

static void	deactivate_another_player(t_game *game)
{
	int	i;

	i = PLAYER_MAX;
	while (--i)
	{
		if (!game->players[i] || !game->players[i]->character.billboard.entity.active)
			continue ;
		game->players[i]->character.billboard.entity.active = false;
		return ;
	}
}

void	key_hook(t_ftm_key_hook_values khv)
{
	t_game	*game;

	game = cub3d()->game;
	pthread_mutex_lock(&cub3d()->game_mutex);
	if (game != cub3d()->game)
	{
		pthread_mutex_unlock(&cub3d()->game_mutex);
		return ;
	}
	call_entity_keys(game, khv);
	if (khv.key == XK_Escape)
	{
		pthread_mutex_unlock(&cub3d()->game_mutex);
		cub3d_exit(0);
		return ;
	}
	if (khv.key == XK_k && khv.down && game->players[0])
		((t_entity *)game->players[0])->controller.keyboard_only =
			!((t_entity *)game->players[0])->controller.keyboard_only;
	if (khv.key == XK_p && khv.down)
		activate_another_player(game);
	if (khv.key == XK_o && khv.down)
		deactivate_another_player(game);
	if (khv.key == XK_F3 && khv.down)
		game->hud.debug_enabled = !game->hud.debug_enabled;
	if (khv.key == XK_F2 && khv.down)
		game->hud.stats_enabled = !game->hud.stats_enabled;
	if (khv.key == XK_F4 && khv.down)
		game->hud.minimap_enabled = !game->hud.minimap_enabled;
	if (khv.key == XK_F5 && khv.down)
		game->hud.action_enabled = !game->hud.action_enabled;
	if (khv.key == XK_F6 && khv.down)
		game->hud.enabled = !game->hud.enabled;
	if (khv.key == XK_F7 && khv.down)
		ftm_window_reload_controllers(&cub3d()->window);
	if (khv.key == XK_F1 && khv.down)
		ftm_window_toggle_fullscreen(&cub3d()->window, (t_size){W_WIDTH, W_HEIGHT});
	pthread_mutex_unlock(&cub3d()->game_mutex);
}
