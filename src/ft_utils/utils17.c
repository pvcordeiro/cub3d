/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils17.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:53 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/23 23:25:55 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

double	ft_angle_distance(t_coords a, t_coords b)
{
	double	distance_x;
	double	distance_y;
	double	angle_to_b;

	distance_x = b.x - a.x;
	distance_y = b.y - a.y;
	angle_to_b = ft_degrees(atan2(distance_y, distance_x));
	return (ft_normalize_angle(angle_to_b - a.yaw));
}
