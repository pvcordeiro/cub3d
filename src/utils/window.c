/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:54:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 08:56:37 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_window(t_window *window, int width, int height, char *title)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (ft_error(ERROR_INIT_MLX));
	window->win = mlx_new_window(window->mlx, width, height, title);
	if (!window->win)
		return (mlx_destroy_display(window->mlx), ft_error(ERROR_INIT_WINDOW));
	window->initialized = true;
	ft_error(ERROR_NO_ERROR);
}

void	destroy_window(t_window *window)
{
	if (!window || !window->initialized)
		return ;
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_display(window->mlx);
}
