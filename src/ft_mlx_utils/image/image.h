/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:22:33 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/14 20:25:05 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <ft_mlx_utils.h>

unsigned int get_modified_pixel(unsigned int (*pm)(void *, unsigned int),
	void *data, unsigned int pixel);

#endif