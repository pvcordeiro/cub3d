/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:35:54 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/21 01:30:24 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"

static void	frame(t_entity *entity, double delta_time)
{
	moviment_frame(entity, delta_time);
	if (entity->character)
		targets_frame((t_character *)entity, PLAYER_FOV);
}

static void	mouse_inv_keys(t_character *character, t_ftm_key_hook_values key_hook_values)
{
	int	new_index;

	new_index = character->inventory_index;
	if (key_hook_values.key == FTM_MOUSE_SCROLL_UP
		&& ft_get_time() - character->last_inventory_scroll >= INVENTORY_SCROLL_DELAY)
	{
		new_index = (new_index + 1) % INVENTORY_SIZE;
			character->last_inventory_scroll = ft_get_time();
	}
	if (key_hook_values.key == FTM_MOUSE_SCROLL_DOWN
		&& ft_get_time() - character->last_inventory_scroll >= INVENTORY_SCROLL_DELAY)
	{
		new_index = (new_index - 1 + INVENTORY_SIZE) % INVENTORY_SIZE;
		character->last_inventory_scroll = ft_get_time();
	}
	if (!character->inventory[new_index])
		return ;
	character->inventory_index = new_index;
}

static t_player_keys	get_player_one_keys(void)
{
	return ((t_player_keys){
		.walking_forward = (t_player_key){XK_w, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.walking_backward = (t_player_key){XK_s, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.walking_left = (t_player_key){XK_a, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.walking_right = (t_player_key){XK_d, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.looking_left = (t_player_key){XK_Left, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.looking_right = (t_player_key){XK_Right, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.action = (t_player_key){XK_e, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.sprinting = (t_player_key){XK_Shift_L, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.move_inventory_index = (t_player_key){XK_r, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.item_use = (t_player_key){XK_space, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
		.item_drop = (t_player_key){XK_q, false, 0.0, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
	});
}

static t_player_keys	get_player_two_keys(void)
{
    return ((t_player_keys){
        .walking_forward = (t_player_key){FTM_GAMEPAD_LSTICK, false, 0.0, 1.0,
            true, {0.0, 0.0, 0}, {1.0, 0.3, 0}},
        .walking_backward = (t_player_key){FTM_GAMEPAD_LSTICK, false, 0.0, 1.0,
            true, {0.0, 0.7, 0}, {1.0, 1.0, 0}},
        .walking_left = (t_player_key){FTM_GAMEPAD_LSTICK, false, 0.0, 1.0, 
            true, {0.0, 0.0, 0}, {0.3, 1.0, 0}},
        .walking_right = (t_player_key){FTM_GAMEPAD_LSTICK, false, 0.0, 1.0, 
            true, {0.7, 0.0, 0}, {1.0, 1.0, 0}},
        .looking_left = (t_player_key){FTM_GAMEPAD_RSTICK, false, 0.0, 1.0, 
            true, {0.0, 0.0, 0}, {0.3, 1.0, 0}},
        .looking_right = (t_player_key){FTM_GAMEPAD_RSTICK, false, 0.0, 1.0,
            true, {0.7, 0.0, 0}, {1.0, 1.0, 0}},
        .action = (t_player_key){FTM_GAMEPAD_X, false, 0.0, 1.0, false,
            {0, 0, 0}, {0, 0, 0}},
        .sprinting = (t_player_key){FTM_GAMEPAD_A, false, 0.0, 1.0, false,
            {0, 0, 0}, {0, 0, 0}},
        .move_inventory_index = (t_player_key){FTM_GAMEPAD_R1, false, 0.0, 1.0,
            false, {0, 0, 0}, {0, 0, 0}},
        .item_use = (t_player_key){FTM_GAMEPAD_R2, true, 0.8, 1.0, false,
            {0, 0, 0}, {0, 0, 0}},
		.item_drop = (t_player_key){FTM_GAMEPAD_L2, true, 0.8, 1.0, false,
			{0, 0, 0}, {0, 0, 0}},
    });
}

static t_player_keys	get_player_keys(t_character *character)
{
	t_player	*player;

	player = (t_player *)character;
	if (character->billboard.entity.type != ENTITY_PLAYER
		|| player == cub3d()->game.players[0])
		return (get_player_one_keys());
	else if (player == cub3d()->game.players[1])
		return (get_player_two_keys());
	return ((t_player_keys){0});
}

static void	item_use_key(bool use, t_character *character)
{
	t_item	*item;

	item = character->inventory[character->inventory_index];
	if (!item)
		return ;
	item->user = NULL;
	if (use)
		item->user = character;
}

static void	item_drop_key(bool drop, t_character *character)
{
	t_item	*item;

	item = character->inventory[character->inventory_index];
	if (!item)
		return ;
	if (drop)
		item->drop(&cub3d()->game, &cub3d()->window, item, character);
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

static void	set_key_bool_value(bool *key_bool, t_player_key player_key,
	t_ftm_key_hook_values key_hook_values)
{
	bool	from_pressure;
	bool	from_coords;

	if (key_hook_values.key != player_key.key)
		return ;
	if (!player_key.use_coords && !player_key.use_pressure)
	{
		*key_bool = key_hook_values.down;
		return ;
	}
	from_pressure = true;
	from_coords = true;
	if (player_key.use_pressure)
		from_pressure = key_hook_values.pressure
			>= player_key.min_pressure && key_hook_values.pressure
			<= player_key.max_pressure;
	if (player_key.use_coords)
		from_coords = key_hook_values.coords.x >= player_key.min_coords.x
			&& key_hook_values.coords.x <= player_key.max_coords.x
			&& key_hook_values.coords.y >= player_key.min_coords.y
			&& key_hook_values.coords.y <= player_key.max_coords.y;
	*key_bool = from_pressure && from_coords;
}

static void	do_half_of_keys(t_controller *cont, t_player_keys keys,
	t_ftm_key_hook_values khv)
{
	set_key_bool_value(&cont->walking_forward, keys.walking_forward, khv);
	set_key_bool_value(&cont->walking_left, keys.walking_left, khv);
	set_key_bool_value(&cont->walking_backward, keys.walking_backward, khv);
	set_key_bool_value(&cont->walking_right, keys.walking_right, khv);
	set_key_bool_value(&cont->looking_right, keys.looking_right, khv);
	set_key_bool_value(&cont->looking_left, keys.looking_left, khv);
	set_key_bool_value(&cont->action, keys.action, khv);
	set_key_bool_value(&cont->sprinting, keys.sprinting, khv);
}

static void	do_cheat_keys(t_entity *entity, t_ftm_key_hook_values khv)
{
	if (khv.key == XK_i && khv.down)
		entity->invencible = !entity->invencible;
	if (khv.key == XK_b && khv.down)
		entity->hard = !entity->hard;
}

static void	do_inv_keys(t_character *character, t_player_keys keys,
	t_ftm_key_hook_values khv)
{
	bool	move_inventory;
	bool	item_use;
	bool	item_drop;

	move_inventory = false;
	item_use = false;
	set_key_bool_value(&move_inventory, keys.move_inventory_index, khv);
	set_key_bool_value(&item_use, keys.item_use, khv);
	set_key_bool_value(&item_drop, keys.item_drop, khv);
	if ((t_character *)cub3d()->game.players[0] == character)
		mouse_inv_keys(character, khv);
	if (move_inventory)
		move_inventory_index(character);
	if (khv.key == keys.item_use.key)
		item_use_key(item_use, character);
	if (khv.key == keys.item_drop.key)
		item_drop_key(item_drop, character);
}

static void	key(t_entity *entity, t_ftm_key_hook_values khv)
{
	t_player_keys	keys;

	if (!entity || !entity->character)
		return ;
	keys = get_player_keys((t_character *)entity);
	do_half_of_keys(&entity->controller, keys, khv);
	do_cheat_keys(entity, khv);
	do_inv_keys((t_character *)entity, keys, khv);
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
