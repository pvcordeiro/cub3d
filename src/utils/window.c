/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:54:58 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/04 16:07:57 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	create_window_e(t_window *window, t_size size, char *title)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (ft_error(ERROR_INIT_MLX));
	window->win = mlx_new_window(window->mlx, size.width, size.height, title);
	if (!window->win)
		return (mlx_destroy_display(window->mlx), ft_error(ERROR_INIT_WINDOW));
	window->canvas = image_new(size);
	if (!window->canvas)
		return (mlx_destroy_window(window->mlx, window->win), mlx_destroy_display(window->mlx),
			ft_error(ERROR_INIT_CANVAS));
	window->initialized = true;
	ft_error(ERROR_NO_ERROR);
}

void	destroy_window(t_window *window)
{
	if (!window || !window->initialized)
		return ;
	free_image(window->canvas);
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
}
