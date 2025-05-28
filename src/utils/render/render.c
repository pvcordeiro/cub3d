/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:49:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/28 17:55:50 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	render_ceiling_and_floor(t_game *game, t_ftm_image *canvas)
{
	unsigned int *pixels;
	pixels = (unsigned int *)canvas->data;
    int i;

	i = 0;
	while (i < canvas->size.width * (canvas->size.height / 2))
	{
		pixels[i] = game->environment.ceiling_color;
		i++;
	}
	i = canvas->size.width * (canvas->size.height / 2);
	while (i < canvas->size.width * canvas->size.height)
	{
		pixels[i] = game->environment.floor_color;
		i++;
	}
}

void	render_game(t_ftm_window *window, t_game *game)
{
	render_ceiling_and_floor(game, window->canvas);
	render_camera(game, window->canvas, &game->camera);
	render_hud(game, window->canvas);
}
