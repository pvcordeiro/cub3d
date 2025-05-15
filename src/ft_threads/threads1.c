/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:30:02 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/15 22:30:13 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_threads.h>

void	ftt_thread_wait(t_ftt_thread *thread)
{
	if (!thread)
		return ;
	while (thread->running)
		ft_sleep(1);
}
