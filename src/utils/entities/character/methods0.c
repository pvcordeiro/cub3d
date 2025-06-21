/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 02:13:08 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

static void	set_using(t_game *game, t_character *character)
{
	char		*key;
	t_sprite	**original;

	key = ft_strf("USING_%c",
		character->inventory[character->inventory_index]->identifier);
	original = hashmap_get_with_identifier(game, game->sprites_3d,
		character->billboard.entity.identifier, key);
	free(key);
	if (!original)
		return ;
	if (character->billboard.sprites != character->using_sprite
		|| character->last_used_item_identifier != character->inventory[character->inventory_index]->identifier)
		fill_3d_sprites_from_src(character->using_sprite, original);
	character->billboard.sprites = character->using_sprite;
	character->last_used_item_identifier = character->inventory[character->inventory_index]->identifier;
}

static bool	walking(t_entity *entity)
{
	return (entity->controller.walking_right
		|| entity->controller.walking_backward
		|| entity->controller.walking_forward
		|| entity->controller.walking_left);
}

static bool	hit(t_character *character)
{
	return (ft_get_time() - character->last_hit < CHARACTER_HIT_DELAY);
}

static bool	using(t_character *character)
{
	t_item	*item;
	bool	is_in_delay;

	item = character->inventory[character->inventory_index];
	if (!item)
		return (false);
	is_in_delay = item->screen_sprite
		&& ft_get_time() - item->last_use < item->screen_sprite->update_delay;
	return (is_in_delay || item->user == character);
}

static void	call_item_frames(t_character *character)
{
	int	i;

	i = -1;
	while (++i < INVENTORY_SIZE)
		if (character->inventory[i] && character->inventory[i]->frame)
			character->inventory[i]->frame(character->inventory[i]);
}

static void	drop_items(t_character *character)
{
	int		i;

	if (!character->drop_items)
		return ;
	if (!character->drop)
	{
		i = -1;
		while (++i < INVENTORY_SIZE)
			if (character->inventory[i] && character->inventory[i]->drop)
				character->inventory[i]->drop(&cub3d()->game,
				&cub3d()->window, character->inventory[i], character);
		return ;
	}
	((t_entity *)character->drop)->coords = ((t_entity *)character)->coords;
	ft_list_add(&cub3d()->game.entities, character->drop, free_entity);
	character->drop = NULL;
}

static void	billions_must_die(t_character *character)
{
	bool	was_already_dead;

	if (character->dead && !character->was_already_dead)
		drop_items(character);
	if (character->dead && character->billboard.entity.health)
		character->dead = false;
	was_already_dead = character->was_already_dead;
	character->was_already_dead = character->dead;
	if ((!character->dead && !was_already_dead)
		|| (character->dead && was_already_dead))
		return ;
	character->billboard.entity.hard = !character->dead;
	character->billboard.entity.targetable = !character->dead;
}

void	character_frame(t_entity *entity, double delta_time)
{
	t_character *character;

	billboard_frame(entity, delta_time);
	character = (t_character *)entity;
	billions_must_die(character);
	if (character->dead)
		character->billboard.sprites = character->death_sprite;
	else if (hit(character))
		character->billboard.sprites = character->hit_sprite;
	else if (using(character))
		set_using(&cub3d()->game, character);
	else if (walking(entity))
		character->billboard.sprites = character->walking_sprite;
	else
		character->billboard.sprites = character->_sprite;
	call_item_frames(character);
}

void	clear_character(void *character)
{
	clear_billboard(character);
}

void	character_action(t_entity *entity, t_character *actioner)
{
	billboard_action(entity, actioner);
}

void	character_shot(t_entity *shooted, t_character *shooter)
{
	t_character	*character;

	billboard_shot(shooted, shooter);
	character = (t_character *)shooted;
	character->last_hit = ft_get_time();
	if (character->dead)
		return ;
	character->last_hit_by_character = shooter;
	if (shooted->health)
		return (fta_play(character->hit_sound));
	fta_play(character->death_sound);
	reset_3d_sprites(character->death_sprite);
	character->dead = true;
}
