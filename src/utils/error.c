/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:00:34 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 00:01:00 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error(t_error _error)
{
	cub3d()->error = _error;
}

void	assert_success(void)
{
	if (cub3d()->error == ERROR_NO_ERROR)
		return ;
}
