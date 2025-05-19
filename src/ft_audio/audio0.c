/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:02:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/19 21:02:23 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"

t_fta_engine	*fta_engine(void)
{
	static t_fta_engine	engine;

	return (&engine);
}

void	fta_init_engine_e(void)
{
	ma_result	result;

	fte_set(ERROR_NO_ERROR);
	result = ma_engine_init(NULL, &fta_engine()->engine);
	if (result != MA_SUCCESS)
		return (fte_set(ERROR_AUDIO_ENGINE_INIT));
	fta_engine()->initialized = true;
}

void	fta_clear_engine(void)
{
	if (!fta_engine()->initialized)
		return ;
	ma_engine_uninit(&fta_engine()->engine);
	fta_engine()->initialized = false;
}

t_fta_audio	*fta_audio_new(const char *path)
{
	t_fta_audio	*audio;
	ma_result	result;

	audio = ft_calloc(1, sizeof(t_fta_audio *));
	if (!audio)
		return (NULL);
	result = ma_sound_init_from_file(&fta_engine()->engine,
			path, 0, NULL, NULL, &audio->sound);
	if (result != MA_SUCCESS)
		return (free(audio), NULL);
	return (audio);
}

void	fta_clear_audio(void *audio)
{
	if (!audio)
		return ;
	ma_sound_uninit(&((t_fta_audio *)audio)->sound);
}

void	fta_free_audio(void *audio)
{
	fta_clear_audio(audio);
	free(audio);
}

void	fta_play(t_fta_audio *audio)
{
	if (!audio)
		return ;
	ma_sound_start(&audio->sound);
}
