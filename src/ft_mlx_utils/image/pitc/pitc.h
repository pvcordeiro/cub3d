/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pitc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:39:15 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 17:17:32 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PITC_H
# define PITC_H

# include "../image.h"

typedef struct s_set_pixel_config
{
	t_ftm_image			*canvas;
	t_ftm_image			*image;
	t_ftm_pitc_config	pitc;
	t_size				index;
	t_coords			scale;
}	t_set_pixel_config;

unsigned int get_modified_pixel(unsigned int (*pm)(void *, unsigned int),
	void *data, unsigned int pixel);
t_coords	get_src_coords(t_ftm_pitc_config pitc,
	t_size index, t_coords scale);
t_coords	get_canvas_coords(t_ftm_pitc_config pitc, t_size index);
void		set_pixel(t_set_pixel_config set_pixel_config);

#endif