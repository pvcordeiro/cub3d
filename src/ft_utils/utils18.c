/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils18.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:40:59 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/06 16:00:28 by paude-so         ###   ########.fr       */
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

char	*ft_strf(const char *format, ...)
{
	va_list	args;
	char	*str;

	va_start(args, format);
	str = ft_strfva(format, &args);
	va_end(args);
	return (str);
}