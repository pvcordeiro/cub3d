/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:47:16 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/24 18:36:49 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "billboards.h"

inline static t_coords	get_centered_bill_cords(t_coords bill_coords)
{
	return ((t_coords){bill_coords.x + 0.5, bill_coords.y + 0.5,
		bill_coords.yaw});
}

inline static double	get_relative_angle(t_coords camera_coords,
	t_coords bill_coords)
{
	double	relative_angle;

	relative_angle = ft_angle_distance(camera_coords, bill_coords);
	if (relative_angle > 180)
		relative_angle -= 360;
	return (relative_angle);
}

inline static t_size	get_size(t_get_size_config gsc)
{
	double		distance;
	double		fov_factor;
	double		fix_fisheye;

	distance = ft_distance(gsc.camera->entity->coords, gsc.bill_coords);
	fix_fisheye = distance * ft_cos_degrees(gsc.relative_angle);
	fov_factor = 73.5 / gsc.camera->fov;
	return ((t_size){(gsc.bill_image_size.width / distance)
		* (gsc.canvas_size.height / 125) * fov_factor, (gsc.bill_image_size.height / fix_fisheye)
		* (gsc.canvas_size.height / 125)});
}

static void	render_billboard(t_billboard *bill, t_ftm_image *canvas,
	t_camera *camera)
{
	t_ftm_image	*image;
	t_size		new_size;
	double		screen_x;
	double		relative_angle;
	t_coords	centered_bill_coords;

	image = get_sprite_image(bill->sprite);
	if (!image)
		return ;
	centered_bill_coords = get_centered_bill_cords(bill->entity.coords);
	relative_angle = get_relative_angle(camera->entity->coords,
			centered_bill_coords);
	if (fabs(relative_angle) > (camera->fov / 2) + bill->entity.size.width)
		return ;
	screen_x = canvas->size.width / 2 + (relative_angle / (camera->fov / 2))
		* (canvas->size.width / 2);
	new_size = get_size((t_get_size_config){camera, centered_bill_coords,
			image->size, canvas->size, relative_angle});
	ftm_put_image_to_canvas(canvas, image,
		(t_ftm_pitc_config){
		(t_coords){screen_x - (new_size.width / 2),
		(canvas->size.height / 2) - (new_size.height / 2), 0},
		false, (t_coords){0, 0, 0},
		(t_coords){0, 0, 0}, true, new_size, NULL, NULL });
}

void	render_billboards(t_game *game, t_ftm_image *canvas, t_camera *camera)
{
	int	i;

	i = -1;
	while (game->billboards[++i])
		render_billboard((t_billboard *)game->billboards[i], canvas, camera);
}
