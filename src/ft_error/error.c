/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:00:34 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 08:59:24 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_error.h>

t_error_storage	*ft_error_storage(void)
{
	static t_error_storage	singleton;

	if (singleton.exit == NULL)
		singleton.exit = exit;
	return (&singleton);
}

void	ft_error(t_error _error)
{
	ft_error_storage()->error = _error;
}

void	ft_error_assert(void)
{
	if (ft_error_storage()->error == ERROR_NO_ERROR)
		return ;
	ft_fputstr(STDERR_FILENO, "Error\n");
	ft_fputstr(STDERR_FILENO, ft_error_message(ft_error_storage()->error));
	ft_error_storage()->exit(ft_error_storage()->error);
}

bool	ft_has_error(void)
{
	if (ft_error_storage()->error == ERROR_NO_ERROR)
		return (false);
	return (true);
}
