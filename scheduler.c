/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 13:21:04 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 20:36:06 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_queues	ft_create_queue(t_coder *coder, int order)
{
	t_queues	queue;

	queue.coder = coder;
	queue.order = order;
	queue.priority = coder->last_compile_start
		+ coder->simulation->data->time_to_burnout;
	return (queue);
}

int	ft_get_queue_order(t_simulation *simulation)
{
	int	order;

	pthread_mutex_lock(&simulation->simulation_state_mutex);
	order = simulation->queue_order;
	simulation->queue_order++;
	pthread_mutex_unlock(&simulation->simulation_state_mutex);
	return (order);
}

int	ft_is_first_request(t_dongle *dongle, t_coder *coder)
{
	t_queues	*request;

	request = ft_heap_peek(dongle);
	if (!request)
		return (0);
	return (request->coder == coder);
}

int	ft_can_acquire_both(t_coder *coder)
{
	t_simulation	*simulation;
	t_dongle		*left;
	t_dongle		*right;

	simulation = coder->simulation;
	left = &simulation->dongles[coder->left_dongle];
	right = &simulation->dongles[coder->right_dongle];
	if (!ft_is_first_request(left, coder))
		return (0);
	if (!ft_is_first_request(right, coder))
		return (0);
	if (!left->is_available || !right->is_available)
		return (0);
	return (1);
}
