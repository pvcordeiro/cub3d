/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:05:32 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/04 01:20:23 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_error_storage
{
	char 	*msg;
	void	(*exit)(int);
}	t_error_storage;

// Set ft_error global error
void			fte_set(const char *msg);

// Check if there is an error
bool			fte_flagged(void);

// ft_error's singleton for storage
t_error_storage	*fte_storage(void);

// Assert that there are no errors.
// If an error is found, it will be printed to stdout
// and the program will exit using the `exit`
// function set in `fte_storage()->exit`
void			fte_assert(void);

#endif
