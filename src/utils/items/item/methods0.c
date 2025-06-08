/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 19:53:38 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "item.h"

void	item_use(t_item *item, t_entity *user)
{
	(void)user;
	fta_play(item->use_sound);
}

void	clear_item(void *data)
{
	(void)data;
}

void	item_frame(t_item *item)
{
	(void)item;
}
