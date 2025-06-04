/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:15:02 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 15:01:04 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"

t_item_creator	get_item_creator(t_identifiers *identifiers, char identifier)
{
	if (ft_list_any(identifiers->item, (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)item_new);
	if (ft_list_any(identifiers->food, (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)food_new);
	if (ft_list_any(identifiers->weapon, (void *)ft_str_equal_char_ptr, &identifier))
		return ((void *)weapon_new);
	return (NULL);
}

void	free_item(void *data)
{
	t_item	*item;

	item = data;
	if (!item)
		return ;
	if (item->clear)
		item->clear(data);
	free(item);
}
