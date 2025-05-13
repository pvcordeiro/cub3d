/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:06:49 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/12 21:12:35 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

double	ft_floor(double x)
{
	if (x < 0 && x != (int)x)
		return ((int)x - 1);
	return ((int)x);
}

double	ft_fmod(double x, double y)
{
	return (x - y * ft_floor(x / y));
}

