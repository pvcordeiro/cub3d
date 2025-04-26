/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:00:34 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 00:21:31 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>

void	error(t_error _error)
{
	ERROR_STORAGE()->error = _error;
}

void	assert_success(void)
{
	if (ERROR_STORAGE()->error == ERROR_NO_ERROR)
		return ;
	ft_fputstr(STDERR_FILENO, get_error_message(ERROR_STORAGE()->error));
	cub3d_exit();
}
