/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 12:50:44 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 20:34:37 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_request_before(t_queues *a, t_queues *b)
{
	t_simulation	*simulation;

	simulation = a->coder->simulation;
	if (!ft_strcmp(simulation->data->scheduler, "fifo"))
		return (a->order < b->order);
	if (a->priority != b->priority)
		return (a->priority < b->priority);
	return (a->order < b->order);
}

static void	ft_swap_queue(t_queues *a, t_queues *b)
{
	t_queues	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_heap_push(t_dongle *dongle, t_queues request)
{
	int	child;
	int	parent;

	child = dongle->queue_size;
	dongle->queue[child] = request;
	dongle->queue_size++;
	while (child > 0)
	{
		parent = (child - 1) / 2;
		if (ft_request_before(&dongle->queue[parent],
				&dongle->queue[child]))
			break ;
		ft_swap_queue(&dongle->queue[parent],
			&dongle->queue[child]);
		child = parent;
	}
}

void	ft_heap_pop(t_dongle *dongle)
{
	int	parent;
	int	child;

	if (dongle->queue_size == 0)
		return ;
	dongle->queue_size--;
	dongle->queue[0] = dongle->queue[dongle->queue_size];
	parent = 0;
	while (1)
	{
		child = parent * 2 + 1;
		if (child >= dongle->queue_size)
			break ;
		if (child + 1 < dongle->queue_size
			&& ft_request_before(&dongle->queue[child + 1],
				&dongle->queue[child]))
			child++;
		if (ft_request_before(&dongle->queue[parent],
				&dongle->queue[child]))
			break ;
		ft_swap_queue(&dongle->queue[parent],
			&dongle->queue[child]);
		parent = child;
	}
}

t_queues	*ft_heap_peek(t_dongle *dongle)
{
	if (dongle->queue_size == 0)
		return (NULL);
	return (&dongle->queue[0]);
}
