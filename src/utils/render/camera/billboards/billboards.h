/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   billboards.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:46:51 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/24 18:34:47 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BILLBOARDS_H
# define BILLBOARDS_H 

# include "../camera.h"

typedef struct s_get_size_config
{
    t_camera    *camera;
    t_coords    bill_coords;
    t_size      bill_image_size;
    t_size      canvas_size;
    double      relative_angle;
}   t_get_size_config;

#endif