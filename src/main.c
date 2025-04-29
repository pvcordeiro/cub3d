/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/29 14:10:20 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	ft_error_storage()->exit = cub3d_exit;
	parse_map_e(&cub3d()->map, argc, argv);
	ft_error_assert();
	create_entities_e(&cub3d()->map, &cub3d()->entities);
	ft_error_assert();
	cub3d_exit(0);
}
