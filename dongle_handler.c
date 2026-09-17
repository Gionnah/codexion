/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 23:16:32 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 20:32:10 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "free_memory.h"

void	ft_release_dongle(t_coder *coder)
{
	t_simulation	*simulation;
	long			time;

	simulation = coder->simulation;
	time = ft_get_current_time_in_ms()
		+ simulation->data->dongle_cooldown;
	pthread_mutex_lock(&simulation->scheduler_mutex);
	simulation->dongles[coder->left_dongle].is_available = 0;
	simulation->dongles[coder->left_dongle].availability_time = time;
	simulation->dongles[coder->right_dongle].is_available = 0;
	simulation->dongles[coder->right_dongle].availability_time = time;
	pthread_cond_broadcast(&simulation->scheduler_cond);
	pthread_mutex_unlock(&simulation->scheduler_mutex);
}

int	ft_acquire_dongle(t_coder *coder)
{
	t_simulation	*simulation;
	t_queues		request;
	struct timespec	timeout;

	simulation = coder->simulation;
	request = ft_create_queue(coder, ft_get_queue_order(simulation));
	pthread_mutex_lock(&simulation->scheduler_mutex);
	ft_add_request(coder, &request);
	while (!simulation->is_simulation_stopped
		&& !ft_can_acquire_both(coder))
	{
		ft_update_dongles(simulation);
		if (ft_can_acquire_both(coder))
			break ;
		timeout = ft_get_timeout(
			ft_get_current_time_in_ms() + 1);
		pthread_cond_timedwait(&simulation->scheduler_cond,
			&simulation->scheduler_mutex, &timeout);
	}
	if (simulation->is_simulation_stopped)
	{
		pthread_mutex_unlock(&simulation->scheduler_mutex);
		return (0);
	}
	simulation->dongles[coder->left_dongle].is_available = 0;
	simulation->dongles[coder->right_dongle].is_available = 0;
	ft_remove_request(coder);
	pthread_mutex_unlock(&simulation->scheduler_mutex);
	return (1);
}
