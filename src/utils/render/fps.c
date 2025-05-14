/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:18:32 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/14 17:56:32 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	update_fps_data(t_fps_data *fps_data, double delta_time)
{
	time_t	current_time;

	fps_data->frametime = delta_time * 1000.0;
	fps_data->frame_count++;
	time(&current_time);
	if (current_time > fps_data->last_update_time)
	{
		fps_data->fps = fps_data->frame_count;
		fps_data->frame_count = 0;
		fps_data->last_update_time = current_time;
		snprintf(fps_data->fps_string, 50, "FPS: %.0f | Frame: %.2f ms", fps_data->fps, fps_data->frametime);
	}
}

void	render_fps_counter(t_fps_data *fps_data, t_ftm_window *window)
{
	if (!fps_data || !window || !window->canvas)
		return ;
	ftm_draw_rectangle(window->canvas, (t_coords){10, 10, 0, 0}, (t_size){180, 20}, (t_ftm_rectangle){0xAA000000, 0x00000000, (t_size){0, 0}});
	ftm_update_window(window);
	mlx_string_put(window->display, window->win, 20, 25, 0xFFFFFFFF, fps_data->fps_string);
}