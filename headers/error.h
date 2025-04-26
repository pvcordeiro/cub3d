/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:05:32 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 00:22:29 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	ERROR_NO_ERROR,
	ERROR_INIT_MLX,
	ERROR_INIT_WINDOW,
}	t_error;

# define ERROR_NO_ERROR_MSG "No Error"
# define ERROR_INIT_MLX_MSG "Error initializing mlx"
# define ERROR_INIT_WINDOW_MSG "Error initializing window"
# define ERROR_INVALID_MSG "Invalid Error"

void	error(t_error _error);
char	*get_error_message(t_error _error);
void	assert_success(void);

# include <cub3d.h>
# define ERROR_STORAGE cub3d

#endif
