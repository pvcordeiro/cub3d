/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:53:37 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/30 01:23:22 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub3d	*cub3d(void)
{
	static t_cub3d	singleton;

	return (&singleton);
}

void	cub3d_exit(int code)
{
	if (cub3d()->window.initialized)
		destroy_window(&cub3d()->window);
	if (cub3d()->map.initialized)
		destroy_map(&cub3d()->map);
	exit(code);
}

int	cub3d_loop(void *_)
{
	(void)_;
	render_map(&cub3d()->map, cub3d()->window.canvas, (t_coords){0, W_HEIGHT - 180, 0, 0}, (t_size){330, 180});
	mlx_put_image_to_window(cub3d()->window.mlx, cub3d()->window.win,
		cub3d()->window.canvas->img_ptr, 0, 0);
	return (0);
}
