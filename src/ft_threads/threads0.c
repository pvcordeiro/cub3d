/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:48:43 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/15 23:12:23 by afpachec         ###   ########.fr       */
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
			if (thread->routine)
				thread->routine(thread->data);
			thread->running = false;
		}
		ft_sleep(1);
	}
}

void	ftt_thread_init(t_ftt_thread *thread)
{
	if (!thread)
		return ;
	pthread_create(&thread->thread, NULL, thread_routine, thread);
}

t_ftt_thread	*ftt_thread_new(void)
{
	t_ftt_thread	*thread;

	thread = ft_calloc(1, sizeof(t_ftt_thread));
	if (!thread)
		return (NULL);
	ftt_thread_init(thread);
	return (thread);
}

void	ftt_thread_run(t_ftt_thread *thread)
{
	if (!thread || thread->running)
		return ;
	thread->running = true;
}

void	ftt_thread_stop(t_ftt_thread *thread)
{
	if (!thread)
		return ;
	thread->running = false;
	pthread_kill(thread->thread, 0);
	ftt_thread_init(thread);
}
