/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 19:54:39 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "weapon.h"

void	weapon_use(t_item *item, t_entity *user)
{
	item_use(item, user);
	printf("pagman pagman pagman\n");
}

void	clear_weapon(void *data)
{
	clear_item(data);
}

void	weapon_frame(t_item *item)
{
	item_frame(item);
}
