/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:35:54 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/19 11:34:32 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static void	frame(t_entity *entity, double delta_time)
{
	moviment_frame(entity, delta_time);
	if (entity->character)
		targets_frame((t_character *)entity, PLAYER_FOV);
}

static void	mouse_inv_keys(t_character *character, int key)
{
	int	new_index;

	new_index = character->inventory_index;
	if (key == XK_MOUSE_SCROLL_UP
		&& ft_get_time() - character->last_inventory_scroll >= INVENTORY_SCROLL_DELAY)
	{
		new_index = (new_index + 1) % INVENTORY_SIZE;
			character->last_inventory_scroll = ft_get_time();
	}
	if (key == XK_MOUSE_SCROLL_DOWN
		&& ft_get_time() - character->last_inventory_scroll >= INVENTORY_SCROLL_DELAY)
	{
		new_index = (new_index - 1 + INVENTORY_SIZE) % INVENTORY_SIZE;
		character->last_inventory_scroll = ft_get_time();
	}
	if (!character->inventory[new_index])
		return ;
	character->inventory_index = new_index;
}

static t_player_keys	get_player_keys(t_character *character)
{
	t_player	*player;

	player = (t_player *)character;
	if (character->billboard.entity.type != ENTITY_PLAYER
		|| player == cub3d()->game.players[0])
		return ((t_player_keys){
			XK_w, XK_s, XK_q, XK_e,
			XK_a, XK_d, XK_f,
			XK_Shift_L, XK_r, XK_space
		});
	if (player == cub3d()->game.players[1])
		return ((t_player_keys){
			XK_u, XK_j, XK_y, XK_i,
			XK_h, XK_k, XK_l,
			XK_Shift_R, XK_o, XK_n
		});
	if (player == cub3d()->game.players[2])
		return ((t_player_keys){
			XK_i, XK_k, 0, 0,
			XK_j, XK_l, XK_o,
			0, XK_u, 0
		});
	if (player == cub3d()->game.players[3])
		return ((t_player_keys){
			XK_Up, XK_Down, 0, 0,
			XK_Left, XK_Right, 0,
			0, 0, 0
		});
	return ((t_player_keys){0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
}

static void	item_key(t_character *character, t_player_keys keys, int key,
	bool down)
{
	t_item	*item;
	bool	mouse_left;

	mouse_left = key == XK_MOUSE_LEFT
		&& (t_character *)cub3d()->game.players[0] == character;
	item = character->inventory[character->inventory_index];
	if (!item || (key != keys.item_use && !mouse_left))
		return ;
	item->user = NULL;
	if (down)
		item->user = character;
}

static void	move_inventory_index(t_character *character)
{
	int	i;

	i = character->inventory_index;
	while (true)
	{
		i += 1;
		if (i < 0)
			i = INVENTORY_SIZE - 1;
		if (i >= INVENTORY_SIZE)
			i = 0;
		if (character->inventory[i] || i == character->inventory_index)
		{
			character->inventory_index = i;
			return ;
		}
	}
}

static void	key(t_entity *entity, int key, bool down)
{
	t_character		*character;
	t_player_keys	keys;

	if (!entity || !entity->character)
		return ;
	character = (t_character *)entity;
	keys = get_player_keys(character);
	if (key == keys.walking_forward)
		entity->controller.walking_forward = down;
	if (key == keys.walking_left)
		entity->controller.walking_left = down;
	if (key == keys.walking_backward)
		entity->controller.walking_backward = down;
	if (key == keys.walking_right)
		entity->controller.walking_right = down;
	if (key == keys.looking_right)
		entity->controller.looking_right = down;
	if (key == keys.looking_left)
		entity->controller.looking_left = down;
	if (key == keys.action)
		entity->controller.action = down;
	if (key == keys.sprinting)
		entity->controller.sprinting = down;
	if (key == XK_i && down)
		entity->invencible = !entity->invencible;
	if (key == XK_b && down)
		entity->hard = !entity->hard;
	if (key == keys.move_inventory_index && down)
		move_inventory_index(character);
	if ((t_character *)cub3d()->game.players[0] == character)
		mouse_inv_keys(character, key);
	item_key(character, keys, key, down);
}

void	init_player_controller(t_entity *entity)
{
	entity->controller.frame = frame;
	entity->controller.key_look_velocity = PLAYER_KEY_LOOK_VELOCITY;
	entity->controller.mouse_look_velocity = PLAYER_MOUSE_LOOK_VELOCITY;
	entity->controller.walk_velocity = PLAYER_WALK_VELOCITY;
	entity->controller.sprint_velocity = PLAYER_SPRINT_VELOCITY;
	entity->controller.key = key;
}
