/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pitc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:39:42 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/18 00:41:17 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pitc.h"

unsigned int inline get_modified_pixel(unsigned int (*pm)(void *, unsigned int),
	void *data, unsigned int pixel)
{
	if (!pm)
		return (pixel);
	return (pm(data, pixel));
}


inline t_coords	get_src_coords(t_ftm_pitc_config pitc,
	t_size index, t_coords scale)
{
	return ((t_coords){pitc.crop_start.x + (int)(index.width
		* scale.x), pitc.crop_start.y + (int)(index.height * scale.y), 0, 0});
}

inline t_coords	get_canvas_coords(t_ftm_pitc_config pitc, t_size index)
{
	return ((t_coords){pitc.coords.x + index.width, pitc.coords.y
		+ index.height, 0, 0});
}
