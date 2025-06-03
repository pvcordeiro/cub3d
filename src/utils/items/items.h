/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:50:57 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 21:31:38 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# include <cub3d.h>

void	*hashmap_get_with_identifier(t_hashmap *hashmap, char identifier, char *rest);

void	init_item(t_game *game, t_ftm_window *window, t_item *item,
			char identifier);
void	item_use(t_item *item, t_entity *user);


void	food_use(t_item *item, t_entity *user);

#endif
