/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:58:13 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/06 17:36:42 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_mlx_utils.h>

void	create_window_e(t_window *window, t_size size, char *title)
{
	window->display = mlx_init();
	if (!window->display)
		return (ft_error(ERROR_INIT_MLX));
	window->win = mlx_new_window(window->display, size.width, size.height, title);
	if (!window->win)
		return (mlx_destroy_display(window->display), ft_error(ERROR_INIT_WINDOW));
	window->canvas = image_new(window, size);
	if (!window->canvas)
		return (mlx_destroy_window(window->display, window->win), mlx_destroy_display(window->display),
			ft_error(ERROR_INIT_CANVAS));
	window->initialized = true;
	ft_error(ERROR_NO_ERROR);
}

void	free_window(void *window)
{
	if (!window || !((t_window *)window)->initialized)
		return ;
	free_image(((t_window *)window)->canvas);
	mlx_destroy_window(((t_window *)window)->display, ((t_window *)window)->win);
	mlx_destroy_display(((t_window *)window)->display);
	free(((t_window *)window)->display);
}

void	update_window(t_window *window)
{
	mlx_put_image_to_window(window->display, window->win,
		window->canvas->img_ptr, 0, 0);
}
