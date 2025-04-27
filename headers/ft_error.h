/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:05:32 by afpachec          #+#    #+#             */
/*   Updated: 2025/04/27 08:59:21 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <ft_utils.h>

# include <unistd.h>
# include <stdlib.h>

typedef enum e_error
{
	ERROR_NO_ERROR,
	ERROR_INIT_MLX,
	ERROR_INIT_WINDOW,
	ERROR_INVALID_ARGS,
}	t_error;

typedef struct s_error_storage
{
	t_error	error;
	void	(*exit)(int);
}	t_error_storage;

# define ERROR_NO_ERROR_MSG "No Error"
# define ERROR_INIT_MLX_MSG "Initializing mlx"
# define ERROR_INIT_WINDOW_MSG "Initializing window"
# define ERROR_INVALID_ARGS_MSG "Invalid Arguments"
# define ERROR_INVALID_MSG "Invalid Error"

void			ft_error(t_error _error);
bool			ft_has_error(void);
char			*ft_error_message(t_error _error);
t_error_storage	*ft_error_storage(void);
void			ft_error_assert(void);

#endif
