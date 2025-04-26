/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:00:34 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 00:26:25 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_error.h>

void	ft_error(t_error _error)
{
	ERROR_STORAGE()->error = _error;
}

void	ft_error_assert(void)
{
	if (ERROR_STORAGE()->error == ERROR_NO_ERROR)
		return ;
	ft_fputstr(STDERR_FILENO, ft_error_message(ERROR_STORAGE()->error));
	ERROR_EXIT_FUNC();
}
