/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:56:07 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/19 21:47:47 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void	set_hooks(t_ftm_window *window)
{
	t_list				*curr;
	t_ftm_controller	*controller;

	curr = window->controllers;
	while (curr)
	{
		controller = curr->data;
		curr = curr->next;
		if (!controller)
			continue ;
		controller->key_hook = window->key_hook;
	}
}

void	ftm_window_reload_controllers(t_ftm_window *window)
{
	if (!window)
		return ;
	ft_list_destroy(&window->controllers);
	window->controllers = ftm_load_controllers();
	if (!window->controllers)
		return ;
	set_hooks(window);
}
