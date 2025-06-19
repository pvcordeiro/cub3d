/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:49:48 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/19 01:23:44 by afpachec         ###   ########.fr       */
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

void	render_game(t_game *game, t_ftm_image *canvas, t_character *character)
{
	render_ceiling_and_floor(game, canvas);
	render_camera(game, canvas, character);
	render_hud(game, canvas, character);
}

static t_player_canvas_data	get_player_canvas_data(t_game *game, t_size cs,
	int player_index)
{
	int						player_count;
	
	player_count = -1;
	while (game->players[++player_count])
		;
	if (player_index >= player_count)
		return ((t_player_canvas_data){(t_size){cs.width / 2, cs.height / 2}, (t_coords){0, cs.height / 2, 0}});
	if (player_count == 1)
		return ((t_player_canvas_data){cs, (t_coords){0, 0, 0}});
	if (player_count == 2)
		return ((t_player_canvas_data){(t_size){cs.width / 2, cs.height}, (t_coords){player_index * cs.width / 2, 0, 0}});
	if (player_count == 3)
	{
		if (player_index == 0 || player_index == 1)
			return ((t_player_canvas_data){(t_size){cs.width / 2, cs.height / 2}, (t_coords){player_index * cs.width / 2, 0, 0}});
		return ((t_player_canvas_data){(t_size){cs.width, cs.height / 2}, (t_coords){0, cs.height / 2, 0}});
	}
	if (player_index == 0 || player_index == 1)
		return ((t_player_canvas_data){(t_size){cs.width / 2, cs.height / 2}, (t_coords){player_index * cs.width / 2, 0, 0}});
	if (player_index == 2 || player_index == 3)
		return ((t_player_canvas_data){(t_size){cs.width / 2, cs.height / 2}, (t_coords){(player_index - 2) * cs.width / 2, cs.height / 2, 0}});
	return ((t_player_canvas_data){(t_size){0, 0}, (t_coords){0, 0, 0}});
}

void	render_players_game(t_game *game, t_ftm_window *window)
{
	t_ftm_image				*player_canvas;
	t_player_canvas_data	player_canvas_data;
	int						i;

	i = -1;
	while (++i < PLAYER_MAX)
	{
		if (!game->players[i])
			return ;
		player_canvas_data = get_player_canvas_data(game, window->canvas->size, i);
		player_canvas = ftm_image_new(window, player_canvas_data.size);
		if (!player_canvas)
			continue ;
		game->players[i]->character.rays = player_canvas_data.size.width;
		render_game(game, player_canvas, (t_character *)game->players[i]);
		ftm_put_image_to_canvas(window->canvas, player_canvas,
			(t_ftm_pitc_config){
				.coords = player_canvas_data.coords,
				.crop = false,
				.resize = false,
				.size = player_canvas_data.size,
				.pixel_modifier = NULL
			});
		ftm_free_image(player_canvas);
	}
}
