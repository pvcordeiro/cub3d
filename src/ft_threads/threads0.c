/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:48:43 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/15 20:16:32 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_threads.h>

static void	*thread_routine(void *data)
{
	t_ftt_thread *thread;

	thread = data;
	while (1)
	{
		if (thread->running)
		{
			thread->routine(thread->data);
			thread->running = false;
		}
		ft_sleep(1);
	}
}

void	ftt_thread_init(t_ftt_thread *thread, void (*routine)(void *), void *data)
{
	if (!thread)
		return ;
	ft_bzero(thread, sizeof(t_ftt_thread));
	thread->routine = routine;
	thread->data = data;
	pthread_create(&thread->thread, NULL, thread_routine, thread);
}

t_ftt_thread	*ftt_thread_new(void (*routine)(void *), void *data)
{
	t_ftt_thread	*thread;

	thread = ft_calloc(1, sizeof(t_ftt_thread));
	if (!thread)
		return (NULL);
	ftt_thread_init(thread, routine, data);
	return (thread);
}

void	ftt_thread_run(t_ftt_thread *thread)
{
	if (!thread || thread->running)
		return ;
	thread->running = true;
}
