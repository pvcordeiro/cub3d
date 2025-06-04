/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils18.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:40:59 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/03 23:51:45 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

bool	ft_str_equal_char_ptr(const char *str, const char *char_ptr)
{
	bool	result;
	char	c_str[2];

	if (str == char_ptr)
		return (true);
	if (!str || !char_ptr)
		return (false);
	c_str[0] = *char_ptr;
	c_str[1] = '\0';
	result = ft_strequal(str, c_str);
	return (result);
}
