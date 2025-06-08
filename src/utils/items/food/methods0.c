/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:31:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 21:29:00 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "food.h"

void	clear_food(void *data)
{
	clear_item(data);
}

void	food_frame(t_item *item)
{
	item_frame(item);
}

