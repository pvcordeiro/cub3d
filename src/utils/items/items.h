/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:57 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/08 17:58:36 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# include <cub3d.h>

// Item
void	init_item(t_game *game, t_ftm_window *window, t_item *item,
			char identifier);
void	clear_food(void *data);
void	item_use(t_item *item);
void	item_frame(t_item *item);

// Food
void	clear_item(void *data);
void	food_frame(t_item *item);
void	food_use(t_item *item);
void	init_food(t_game *game, t_ftm_window *window, t_food *food,
			char identifier);

// Weapon
void	clear_weapon(void *data);
void	weapon_frame(t_item *item);
void	weapon_use(t_item *item);
void	init_weapon(t_game *game, t_ftm_window *window, t_weapon *weapon,
			char identifier);

// Ammo
void	clear_ammo(void *data);
void	ammo_use(t_item *item);
void	ammo_frame(t_item *item);
void	init_ammo(t_game *game, t_ftm_window *window, t_ammo *ammo,
			char identifier);

#endif
