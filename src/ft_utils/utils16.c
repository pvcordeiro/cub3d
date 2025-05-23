/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:53 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/23 17:47:13 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

double	ft_cos_degrees(double angle_degree)
{
	return (cos(ft_normalize_angle(angle_degree) * FT_UTILS_PI / 180.0));
}

double	ft_sin_degrees(double angle_degree)
{
	return (sin(ft_normalize_angle(angle_degree) * FT_UTILS_PI / 180.0));
}


double	ft_distance(t_coords a, t_coords b)
{
	return (ft_sqrt(ft_pow(a.x - b.x, 2) + ft_pow(a.y - b.y, 2)));
}
