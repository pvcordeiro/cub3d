/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paude-so <paude-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:05:32 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/04 15:15:17 by paude-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

typedef enum e_error
{
	ERROR_NO_ERROR,
	ERROR_INIT_MLX,
	ERROR_INIT_WINDOW,
	ERROR_INVALID_ARGS,
	ERROR_INVALID_MAP,
	ERROR_MAP_OPEN,
	ERROR_MAP_ALREADY_INITIALIZED,
	ERROR_MAP_READ,
	ERROR_DUPLICATE_TYPE,
	ERROR_MAP_HASHMAP,
	ERROR_ENTITY_CREATION,
	ERROR_INIT_CANVAS,
	ERROR_INVALID_TYPE,
	ERROR_MISSING_TEXTURE_LOAD,
	ERROR_INIT_MAP_GRID_TRIPLE,
	ERROR_INIT_MAP_GRID_DOUBLE,
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
# define ERROR_INVALID_MAP_MSG "Invalid Map"
# define ERROR_MAP_OPEN_MSG "Map open error"
# define ERROR_MAP_ALREADY_INITIALIZED_MSG "Map already initialized"
# define ERROR_MAP_READ_MSG "Map read error"
# define ERROR_DUPLICATE_TYPE_MSG "Duplicate Type"
# define ERROR_MAP_HASHMAP_MSG "Map Hashmap error"
# define ERROR_INVALID_TYPE_MSG "Invalid Type"
# define ERROR_ENTITY_CREATION_MSG "Entity Creation error"
# define ERROR_INIT_CANVAS_MSG "Initializing canvas"
# define ERROR_MISSING_TEXTURE_LOAD_MSG "Missing Texture Load"
# define ERROR_INIT_MAP_GRID_TRIPLE_MSG "Initializing map grid triple"
# define ERROR_INIT_MAP_GRID_DOUBLE_MSG "Initializing map grid double"
# define ERROR_INVALID_MSG "Invalid Error"

void			ft_error(t_error _error);
bool			ft_has_error(void);
char			*ft_error_message(t_error _error);
t_error_storage	*ft_error_storage(void);
void			ft_error_assert(void);

#endif
