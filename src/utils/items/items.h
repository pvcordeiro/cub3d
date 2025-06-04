/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:57 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 00:55:06 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# include <cub3d.h>

void	init_item(t_game *game, t_ftm_window *window, t_item *item,
			char identifier);
void	clear_food(void *data);
void	item_use(t_item *item, t_entity *user);


void	food_use(t_item *item, t_entity *user);
void	clear_item(void *data);
void	init_food(t_game *game, t_ftm_window *window, t_food *food,
			char identifier);
#endif
