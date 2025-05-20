/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils15.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:26:55 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 14:40:11 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_utils.h>

t_list	*ft_list_clone(t_list *list)
{
	t_list	*new_list;
	t_list	*curr;

	if (!list)
		return (NULL);
	new_list = NULL;
	curr = list;
	while (curr)
	{
		ft_list_add(&new_list, curr->data, curr->data_free);
		curr = curr->next;
	}
	return (new_list);
}

void	ft_list_reverse(t_list **list)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	if (!list || !*list)
		return ;
	prev = NULL;
	curr = *list;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*list = prev;
}

void	ft_sleep(double miliseconds)
{
	t_time	start;

	start = ft_get_time();
	while (ft_get_time() - start < miliseconds)
		;
}

void	ft_list_clear_without_free(t_list *list)
{
	while (list)
	{
		list->data = NULL;
		list->data_free = NULL;
		list = list->next;
	}
}
