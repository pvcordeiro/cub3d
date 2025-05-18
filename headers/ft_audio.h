/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_audio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:01:45 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/18 12:13:47 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AUDIO_H
# define FT_AUDIO_H

# include <ft_utils.h>
# include <ft_error.h>
# include <miniaudio.h>

typedef struct s_fta_audio
{
	ma_sound	sound;
}	t_fta_audio;

typedef struct s_fta_engine
{
	ma_engine	engine;
}	t_fta_engine;

void		fta_init_engine_e(void);
t_fta_audio	*fta_audio_new(const char *path);
void		fta_play(t_fta_audio *audio);

#endif