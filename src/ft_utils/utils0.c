/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:44:32 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/03 15:44:49 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

double ft_normalize_angle(double angle)
{
    angle = fmod(angle, 360.0);
    if (angle < 0)
        angle += 360.0;
    return angle;
}
