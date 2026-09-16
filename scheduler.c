/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanitriniala <hanitriniala@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 13:21:04 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 22:04:01 by hanitrinial      ###   ########.fr       */
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

int	ft_request_dongle(t_coder *coder, int index)
{
	t_simulation	*simulation;
	t_dongle		*dongle;
	t_queues		request;

	simulation = coder->simulation;
	dongle = &simulation->dongles[index];
	request = ft_create_queue(coder,
			ft_get_queue_order(simulation));
	pthread_mutex_lock(&dongle->mutex);
	ft_heap_push(dongle, request);
	while (ft_heap_peek(dongle)->coder != coder
		|| !dongle->is_available)
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	dongle->is_available = 0;
	ft_heap_pop(dongle);
	pthread_mutex_unlock(&dongle->mutex);
	return (0);
}

int	ft_is_first_request(t_dongle *dongle, t_coder *coder)
{
	t_queues	*request;

	request = ft_heap_peek(dongle);
	if (!request)
		return (0);
	return (request->coder == coder);
}
