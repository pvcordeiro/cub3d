/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 15:06:20 by paude-so         ###   ########.fr       */
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
