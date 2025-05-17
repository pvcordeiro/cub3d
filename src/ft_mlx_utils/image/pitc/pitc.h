/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pitc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:39:15 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/18 00:41:45 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PITC_H
# define PITC_H

# include "../image.h"

unsigned int get_modified_pixel(unsigned int (*pm)(void *, unsigned int),
	void *data, unsigned int pixel);
inline t_coords	get_src_coords(t_ftm_pitc_config pitc,
	t_size index, t_coords scale);
inline t_coords	get_canvas_coords(t_ftm_pitc_config pitc, t_size index);

#endif