/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/28 17:22:57 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	ft_error_storage()->exit = cub3d_exit;
	parse_map_e(&cub3d()->map, argc, argv);
	ft_error_assert();
	create_window_e(&cub3d()->window, W_WIDTH, W_HEIGHT, W_TITLE);
	ft_error_assert();
	ft_fputstr(1, "RAW MAP:\n");
	ft_fprint_strv(1, cub3d()->map.raw);
	ft_fputstr(1, "\nTYPES:\n");
	ft_fprint_hashmap(1, cub3d()->map.types);
	ft_fputstr(1, "\nMAP:\n");
	ft_fprint_strv(1, cub3d()->map.map);
	cub3d_exit(0);
}
