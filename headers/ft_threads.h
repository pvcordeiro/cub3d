/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:48:00 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/15 20:09:47 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_THREADS_H
# define FT_THREADS_H

// External Libs
# include <pthread.h>

// Internal Libs
# include <ft_utils.h>

typedef struct s_ftt_thread
{
	pthread_t	thread;
	bool		running;
	void		(*routine)(void *);
	void		*data;
}	t_ftt_thread;

#endif