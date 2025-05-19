/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:25 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/19 23:14:13 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <cub3d.h>

typedef struct s_raycasting_slice
{
	t_ftm_image	*canvas;
	t_player	*player;
	int			starting_index;
	int			ending_index;
}	t_raycasting_slice;

void	render_minimap(t_game *game, t_ftm_image *canvas, t_coords coords, t_size size);
void	render_hud(t_game *game, t_ftm_image *canvas);

#endif