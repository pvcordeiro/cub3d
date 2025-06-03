/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:15:02 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 21:27:46 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"

void	*hashmap_get_with_identifier(t_hashmap *hashmap, char identifier, char *rest)
{
	char	*key;
	void	*data;

	key = ft_strf("%c_%s", identifier, rest);
	data = ft_hashmap_get_value(hashmap, key);
	return (free(key), data);
}
