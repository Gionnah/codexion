/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 13:21:04 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 13:26:34 by mvelonja         ###   ########.fr       */
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

static int	ft_get_queue_order(t_simulation *simulation)
{
	int	order;

	pthread_mutex_lock(&simulation->simulation_state_mutex);
	order = simulation->queue_order;
	simulation->queue_order++;
	pthread_mutex_unlock(&simulation->simulation_state_mutex);
	return (order);
}
