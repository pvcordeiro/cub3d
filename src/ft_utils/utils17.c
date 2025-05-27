/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils17.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:45:53 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/28 00:37:02 by afpachec         ###   ########.fr       */
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

bool	ft_is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (false);
	return (closedir(dir), true);
}

char	*ft_clean_path(const char *path)
{
	if (!path)
		return (NULL);
	if (ft_str_endswith(path, "/"))
		return (ft_strndup(path, ft_strlen(path) - 1));
	return (ft_strdup(path));
}

void	ft_strvorder(char **strv, const void *data, bool (*cmp)(const void
	*data, const char *, const char *))
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!strv || !cmp)
		return ;
	i = -1;
	while (strv[++i])
	{
		j = i;
		while (strv[++j])
		{
			if (!cmp(data, strv[i], strv[j]))
				continue ;
			tmp = strv[i];
			strv[i] = strv[j];
			strv[j] = tmp;
		}
	}
}
