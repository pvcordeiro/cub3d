/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:18:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/22 21:24:06 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	set_audio_configs_e(t_game *game)
{
	t_fta_audio			*audio;
	t_element			*el;
	t_element			*curr;
	char				*key;

	fte_set(ERROR_NO_ERROR);
	el = *game->map->types->table;
	while (el)
	{
		curr = el;
		el = el->next;
		key = NULL;
		if (ft_str_endswith(curr->key, "_SOUND_VOLUME"))
		{
			key = ft_strndup(curr->key, ft_strlen(curr->key) - 13);
			audio = ft_hashmap_get_value(game->sounds, key);
			if (!audio)
				return (fte_set(ERROR_AUDIO_CONFIG_ON_INVALID));
			fta_audio_config(audio, (t_fta_audio_config){ft_atof(curr->value), audio->config.loop});
			continue ;
		}
		else if (ft_str_endswith(curr->key, "_SOUND_LOOP"))
		{
			key = ft_strndup(curr->key, ft_strlen(curr->key) - 11);
			audio = ft_hashmap_get_value(game->sounds, key);
			if (!audio)
				return (fte_set(ERROR_AUDIO_CONFIG_ON_INVALID));
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

	fte_set(ERROR_NO_ERROR);
	el = *game->map->types->table;
	while (el)
	{
		curr = el;
		el = el->next;
		if (!ft_str_endswith(curr->key, "_SOUND"))
			continue ;
		if (!ft_str_endswith(curr->value, ".mp3"))
			return (fte_set(ERROR_INVALID_AUDIO_FORMAT));
		audio = fta_audio_new(curr->value);
		if (!audio && fta_engine()->initialized)
			return (fte_set(ERROR_LOAD_SOUND));
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

void	init_camera(t_game *game)
{
	game->camera.entity = (t_entity *)game->player;
	game->camera.rays = PLAYER_RAYS;
	game->camera.fov = PLAYER_FOV;
}

void	init_hud(t_game *game)
{
	game->hud.enabled = true;
}
