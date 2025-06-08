/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 22:05:10 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drop.h"

static void	set_sprite(t_drop	*drop)
{
	t_item	*prev_item;
	t_item	*item;
	int		i;

	item = drop->billboard.entity.inventory[0];
	prev_item = drop->billboard.entity.inventory[1];
	if (!item)
		return ;
	if (prev_item == item)
		return ;
	prev_item = item;
	i = -1;
	while (++i <= 360)
		drop->billboard.sprites[i] = item->icon_sprite;
}

static void	do_the_thing(t_game *game, t_drop *drop)
{
	int			i;
	t_entity	*entity;
	t_item		*item;

	item = drop->billboard.entity.inventory[0];
	if (!item || (!drop->auto_use && !drop->auto_pickup))
		return ;
	i = -1;
	while (game->billboards[++i])
	{
		entity = game->billboards[i];
        if (entity == (t_entity *)drop || entity->type != ENTITY_PLAYER
            || drop->billboard.entity.coords.x + entity->size.width < entity->coords.x
            || drop->billboard.entity.coords.x - entity->size.width > (entity->coords.x + entity->size.width)
            || drop->billboard.entity.coords.y + entity->size.height < entity->coords.y
            || drop->billboard.entity.coords.y - entity->size.height > (entity->coords.y + entity->size.height))
			continue ;
		if (drop->auto_use)
		{
			item->using = true;
			drop->billboard.entity.active = false;
		}
		else if (drop->auto_pickup)
		{
			add_item_to_inventory(entity, item);
			drop->billboard.entity.active = false;
		}
	}
}

void	drop_frame(t_entity *entity, double delta_time)
{
	t_drop	*drop;

	billboard_frame(entity, delta_time);
	drop = (t_drop *)entity;
	set_sprite(drop);
	do_the_thing(&cub3d()->game, drop);
}

void	clear_drop(void *drop)
{
	clear_billboard(drop);
	if (!drop)
		return ;
	free_item(((t_entity *)drop)->inventory[0]);
}

void	drop_action(t_entity *entity, t_entity *actioner)
{
	billboard_action(entity, actioner);
}

void	drop_shot(t_entity *shooted, t_entity *shooter)
{
	billboard_shot(shooted, shooter);
}
