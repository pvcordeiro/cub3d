/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:02:20 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 01:26:39 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "audio.h"

t_fta_engine	*fta_engine(void)
{
	static t_fta_engine	engine;

	return (&engine);
}

void	fta_init_e(void)
{
	ma_result	result;

	fte_set(NULL);
	result = ma_engine_init(NULL, &fta_engine()->engine);
	if (result != MA_SUCCESS)
		return (fte_set("audio engine init"));
	fta_engine()->initialized = true;
}

void	fta_destroy(void)
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
	int			i;

	if (!fta_engine()->initialized)
		return (NULL);
	audio = ft_calloc(1, sizeof(t_fta_audio));
	if (!audio)
		return (NULL);
	audio->config.volume = 1.0;
	result = ma_sound_init_from_file(&fta_engine()->engine,
			path, 0, NULL, NULL, &audio->sound[0]);
	if (result != MA_SUCCESS)
		return (free(audio), NULL);
	i = 0;
	while (++i < FT_AUDIO_SOUND_INSTANCES)
	{
		result = ma_sound_init_copy(&fta_engine()->engine, &audio->sound[0], 0, NULL, &audio->sound[i]);
		if (result != MA_SUCCESS)
			return (fta_free_audio(audio), NULL);
	}
	return (audio);
}

void	fta_audio_config(t_fta_audio *audio, t_fta_audio_config config)
{
	int	i;

	if (!audio || !fta_engine()->initialized)
		return ;
	if (config.volume < 0.0)
		config.volume = 0.0;
	else if (config.volume > 1.0)
		config.volume = 1.0;
	audio->config = config;
	i = -1;
	while (++i < FT_AUDIO_SOUND_INSTANCES)
	{
		ma_sound_set_looping(&audio->sound[i], config.loop);
		ma_sound_set_volume(&audio->sound[i], config.volume);
	}
}

void	fta_clear_audio(void *audio)
{
	int	i;

	if (!audio || !fta_engine()->initialized)
		return ;
	i = -1;
	while (++i < FT_AUDIO_SOUND_INSTANCES)
		ma_sound_uninit(&((t_fta_audio *)audio)->sound[i]);
}

void	fta_free_audio(void *audio)
{
	fta_clear_audio(audio);
	free(audio);
}

void	fta_play(t_fta_audio *audio)
{
	static int	i;

	if (!audio || !fta_engine()->initialized)
		return ;
	++i;
	if (i < 0 || i >= FT_AUDIO_SOUND_INSTANCES)
		i = 0;
	ma_sound_start(&audio->sound[i]);
}
