/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:51:04 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 22:28:48 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <ft_mlx_utils.h>
# include <X11/extensions/Xrandr.h>
# include <mlx_int.h>

int	window_loop_hook(void *window);
int window_key_down_hook(int key, void *window);
int window_key_up_hook(int key, void *window);
int window_exit_hook(void *window);
int window_mouse_hook(int x, int y, void *window);

#endif