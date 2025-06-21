/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:18:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 16:18:42 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	set_audio_configs_e(t_game *game)
{
	t_fta_audio			*audio;
	t_element			*el;
	t_element			*curr;
	char				*key;

	fte_set(NULL);
	el = game->map->types->table;
	while (el)
	{
		curr = el;
		el = el->next;
		key = NULL;
		if (ft_str_endswith(curr->key, "_SOUND_VOLUME"))
		{
			key = ft_strndup(curr->key, ft_strlen(curr->key) - 13);
			audio = ft_hashmap_get_value(game->sounds, key);
			free(key);
			if (!audio)
				continue ;
			fta_audio_config(audio, (t_fta_audio_config){ft_atof(curr->value), audio->config.loop});
			continue ;
		}
		else if (ft_str_endswith(curr->key, "_SOUND_LOOP"))
		{
			key = ft_strndup(curr->key, ft_strlen(curr->key) - 11);
			audio = ft_hashmap_get_value(game->sounds, key);
			free(key);
			if (!audio)
				continue ;
			fta_audio_config(audio, (t_fta_audio_config){audio->config.volume, ft_strequal(curr->value, "TRUE")});
			continue ;
		}
		free(key);
	}
}

void	init_sounds_e(t_game *game)
{
	t_fta_audio			*audio;
	t_element			*el;
	t_element			*curr;
	char				*key;

	fte_set(NULL);
	el = game->map->types->table;
	while (el)
	{
		curr = el;
		el = el->next;
		if (!ft_str_endswith(curr->key, "_SOUND"))
			continue ;
		if (!ft_str_endswith(curr->value, ".mp3"))
			return (fte_set("invalid audio format"));
		audio = fta_audio_new(curr->value);
		if (!audio && fta_engine()->initialized)
			return (fte_set("audio load"));
		if (!audio)
			continue ;
		key = ft_strndup(curr->key, ft_strlen(curr->key) - 6);
		ft_hashmap_set(game->sounds, key, audio, fta_free_audio);
		free(key);
	}
	set_audio_configs_e(game);
	if (fte_flagged())
		return ;
}

static void	init_stats_hud(t_game *game)
{
	t_sprite	*sprite;
	char		*key;

	game->hud.stats_enabled = !ft_strequal(ft_hashmap_get_value(game->map->types, "STATS_HUD"), "FALSE");
	game->hud.stats_font = ft_hashmap_get_value(game->fonts, "STATS_HUD");
	if (!game->hud.stats_font)
		game->hud.stats_font = ft_hashmap_get_value(game->fonts, "DEFAULT");
	game->hud.stats.prev_health = -1;
	game->hud.stats.states = -1;
	while (++game->hud.stats.states || true)
	{
		key = ft_strf("STATS_HUD_%d", game->hud.stats.states + 1);
		sprite = ft_hashmap_get_value(game->sprites, key);
		free(key);
		if (!sprite)
			break ;
		ft_list_add(&game->hud.stats.states_list, sprite, NULL);
	}
	if (game->hud.stats.states)
		game->hud.stats.sprite = ft_list_index(game->hud.stats.states_list, 0)->data;
}

static void	init_debug_hud(t_game *game)
{
	game->hud.debug_enabled = ft_strequal(ft_hashmap_get_value(game->map->types, "DEBUG_HUD"), "TRUE");
	game->hud.debug_font = ft_hashmap_get_value(game->fonts, "DEBUG_HUD");
	if (!game->hud.debug_font)
		game->hud.debug_font = ft_hashmap_get_value(game->fonts, "DEFAULT");
}

static void	init_action_hud(t_game *game)
{
	game->hud.action_enabled = !ft_strequal(ft_hashmap_get_value(game->map->types, "ACTION_HUD"), "FALSE");
	game->hud.action_font = ft_hashmap_get_value(game->fonts, "ACTION_HUD");
	if (!game->hud.action_font)
		game->hud.action_font = ft_hashmap_get_value(game->fonts, "DEFAULT");
}

void	init_hud(t_game *game)
{
	game->hud.enabled = !ft_strequal(ft_hashmap_get_value(game->map->types, "HUD"), "FALSE");
	game->hud.minimap_enabled = !ft_strequal(ft_hashmap_get_value(game->map->types, "MINIMAP_HUD"), "FALSE");
	init_stats_hud(game);
	init_debug_hud(game);
	init_action_hud(game);
}
