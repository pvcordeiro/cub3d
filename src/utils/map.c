/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:42:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 11:33:33 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	parse_map(t_map *map, int argc, char **argv)
{
	if (argc != 2 || !argv || !argv[0] || !argv[1] || argv[2])
		return (ft_error(ERROR_INVALID_ARGS));
	map->path = argv[1];
}
