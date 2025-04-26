/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:15:19 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 00:33:36 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(void)
{
	create_window(&cub3d()->window, 500, 500, "PAGMAN");
	ft_error_assert();
	printf("Hello cub3d! :)\n");
	while (true)
		;
}
