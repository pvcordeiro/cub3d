/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/07 19:40:50 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "item.h"

void	clear_item(void *data)
{
	(void)data;
}

void	item_frame(t_item *item)
{
	bool	play_sound1;
	bool	play_sound2;

	play_sound1 = !item->single_use && item->using
		&& item->use_sound
		&& item->screen_sprite
		&& ft_get_time() - item->last_sound_play >= item->screen_sprite->update_delay * 2;
	play_sound2 = item->single_use && !item->already_using && item->using;
	if (play_sound1 || play_sound2)
	{
		item->last_sound_play = ft_get_time();
		fta_play(item->use_sound);
	}
	if (((!item->single_use && item->using) || (item->single_use && !item->already_using && item->using)) && item->screen_use_sprite)
	{
		item->screen_sprite = item->screen_use_sprite;
		item->screen_sprite->index = 0;
		item->screen_sprite->loop = !item->single_use;
	}
	else
		item->screen_sprite = item->_screen_sprite;
	item->already_using = item->using;
}
