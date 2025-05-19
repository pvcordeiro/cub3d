/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:18:52 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/19 21:28:13 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_sounds_e(t_game *game)
{
	t_fta_audio	*audio;
	t_element	*el;
	t_element	*curr;
	char		*key;

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
}
