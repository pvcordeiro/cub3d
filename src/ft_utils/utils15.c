/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils15.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:02:59 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/12 21:06:41 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

double	ft_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

double	ft_pow(double base, double exp)
{
	double	result;

	result = 1.0;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}

double	ft_sqrt(double x)
{
	double	guess;
	double	prev_guess;

	if (x < 0)
		return (-1);
	if (x == 0 || x == 1)
		return (x);
	guess = x / 2;
	prev_guess = 0;
	while (ft_abs(guess - prev_guess) > 0.000001)
	{
		prev_guess = guess;
		guess = (guess + x / guess) / 2;
	}
	return (guess);
}

double	ft_distance(t_coords a, t_coords b)
{
	return (ft_sqrt(ft_pow(a.x - b.x, 2) + ft_pow(a.y - b.y, 2)));
}
