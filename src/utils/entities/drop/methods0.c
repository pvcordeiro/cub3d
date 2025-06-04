/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 15:19:18 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drop.h"

static void	set_sprite(t_drop	*drop)
{
	int	i;

	if (drop->_prev_item == drop->item)
		return ;
	drop->_prev_item = drop->item;
	i = -1;
	while (++i <= 360)
		drop->billboard.sprites[i] = drop->item->icon_sprite;
}

static void	do_the_auto_use(t_game *game, t_drop *drop)
{
	int			i;
	t_entity	*entity;

	if (!drop->item || !drop->auto_use || !drop->item->use)
		return ;
	i = -1;
	while (game->billboards[++i])
	{
		entity = game->billboards[i];
        if (entity == (t_entity *)drop
            || drop->billboard.entity.coords.x + entity->size.width < entity->coords.x
            || drop->billboard.entity.coords.x - entity->size.width > (entity->coords.x + entity->size.width)
            || drop->billboard.entity.coords.y + entity->size.height < entity->coords.y
            || drop->billboard.entity.coords.y - entity->size.height > (entity->coords.y + entity->size.height))
			continue ;
		drop->item->use(drop->item, entity);
		drop->billboard.entity.active = false;
	}
}

void	drop_frame(t_entity *entity, double delta_time)
{
	t_drop	*drop;

	billboard_frame(entity, delta_time);
	drop = (t_drop *)entity;
	set_sprite(drop);
	do_the_auto_use(&cub3d()->game, drop);
}

void	clear_drop(void *drop)
{
	clear_billboard(drop);
	if (!drop)
		return ;
	free_item(((t_drop *)drop)->item);
}

void	drop_action(t_entity *entity, t_entity *actioner)
{
	billboard_action(entity, actioner);
}
