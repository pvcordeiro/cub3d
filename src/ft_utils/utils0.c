/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:44:32 by paude-so          #+#    #+#             */
/*   Updated: 2025/05/12 21:04:26 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

double	ft_normalize_angle(double angle)
{
	angle = ft_fmod(angle, 360.0);
	if (angle < 0)
		angle += 360.0;
	return (angle);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*nptr && *nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

t_list	*ft_list_index(t_list *list, size_t index)
{
	size_t	i;

	i = -1;
	while (list && ++i < index)
		list = list->next;
	return (list);
}

bool	ft_is_file(char *path)
{
	int	fd;

	if (!path)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

unsigned int	ft_rgb_to_unsigned(char *rgb_str, char *separator)
{
	unsigned int	color;
	char			**strs;

	strs = ft_split(rgb_str, separator);
	color = ft_atoi(strs[0]);
	color *= 0x00000100;
	color += ft_atoi(strs[1]);
	color *= 0x00000100;
	color += ft_atoi(strs[2]);
	ft_strvfree(strs);
	color += 0xFF000000;
	return (color);
}
