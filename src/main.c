/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 12:10:52 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	parse_map(&cub3d()->map, argc, argv);
	ft_error_assert();
	create_window(&cub3d()->window, W_WIDTH, W_HEIGHT, W_TITLE);
	ft_error_assert();
	ft_fprint_strv(1, cub3d()->map.raw);
	while (true);
}
