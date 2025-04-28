/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils13.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:52:26 by paude-so          #+#    #+#             */
/*   Updated: 2025/04/28 19:10:05 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

bool	ft_str_all(char *str, bool (*func)(char))
{
	size_t	i;

	if (!str || !func)
		return (false);
	i = -1;
	while (str[++i])
		if (!func(str[i]))
			return (false);
	return (true);
}

bool	ft_str_endswith(char *str, char *ending)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(ending) - 1;
	if (i < j)
		return (false);
	while (j)
	{
		if (str[i--] != ending[j--])
			return (false);
	}
	return (true);
}

char	*ft_strtrim(char *s)
{
	char	*start;
	char	*end;
	size_t	len;

	if (!s)
		return (NULL);
	start = s;
	end = s + ft_strlen(s) - 1;
	while (*start && ft_isspace(*start))
		start++;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	return (ft_strndup(start, len));
}

t_time	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
