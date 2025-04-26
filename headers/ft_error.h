/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:05:32 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 00:26:20 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

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

void	ft_error(t_error _error);
char	*ft_error_message(t_error _error);
void	ft_error_assert(void);

# include <cub3d.h>
# define ERROR_STORAGE cub3d
# define ERROR_EXIT_FUNC cub3d_exit

#endif
