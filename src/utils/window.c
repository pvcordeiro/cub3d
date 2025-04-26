/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:54:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 00:15:48 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	create_window(t_window *window, int width, int height, char *title)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (error(ERROR_INIT_MLX), false);
	window->win = mlx_new_window(window->mlx, width, height, title);
	if (!window->win)
		return (error(ERROR_INIT_WINDOW),
			mlx_destroy_display(window->mlx), false);
	window->initialized = true;
	return (error(ERROR_NO_ERROR), true);
}

void	destroy_window(t_window *window)
{
	if (!window || !window->initialized)
		return ;
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_display(window->mlx);
}
