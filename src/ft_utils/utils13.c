/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils13.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:52:26 by paude-so          #+#    #+#             */
/*   Updated: 2025/04/27 12:15:00 by afpachec         ###   ########.fr       */
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
