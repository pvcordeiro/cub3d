/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:37:28 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/04 13:29:42 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static unsigned convert_color_to_hex(char *str)
{
	unsigned color;
	char **strs;

	strs = ft_split(str, ",");
	ft_fprint_strv(1, strs);
	color = ft_atoi(strs[0]);
	color *= 0x000100;
	color += ft_atoi(strs[1]);
	color *= 0x000100;
	color += ft_atoi(strs[2]);
	free(strs);
	printf("COLOUR: %X\n", color);
	return (color);
}

void	set_map_colors(t_map *map)
{
	map->ceiling_color = convert_color_to_hex(ft_hashmap_get_value(map->types, "C"));
	map->floor_color = convert_color_to_hex(ft_hashmap_get_value(map->types, "F"));
}
