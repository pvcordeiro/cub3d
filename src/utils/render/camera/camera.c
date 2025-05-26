/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:59 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/26 23:13:04 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	render_camera(t_game *game, t_ftm_image *canvas, t_camera *camera)
{
	static unsigned int	prev_ray_count;

	if (prev_ray_count != camera->rays)
	{
		camera->ray_distances = ft_calloc(camera->rays, sizeof(double));
		prev_ray_count = camera->rays;
	}
	if (!camera->ray_distances)
		return ;
	render_walls(game, canvas, camera);
	render_billboards(game, canvas, camera);
}
