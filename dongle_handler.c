/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanitriniala <hanitriniala@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 23:16:32 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 22:04:09 by hanitrinial      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "free_memory.h"

static void	ft_lock_dongle(t_coder *coder, int index)
{
	t_simulation	*simulation;
	t_dongle		*dongle;
	t_queues		request;
	struct timespec	timeout;

	simulation = coder->simulation;
	dongle = &simulation->dongles[index];
	request = ft_create_queue(coder, ft_get_queue_order(simulation));
	pthread_mutex_lock(&dongle->mutex);
	ft_heap_push(dongle, request);
	while (ft_heap_peek(dongle)->coder != coder || !dongle->is_available)
	{
		if (!dongle->is_available)
		{
			timeout = ft_get_timeout(dongle->availability_time);
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &timeout);
			if (ft_get_current_time_in_ms() >= dongle->availability_time)
				dongle->is_available = 1;
		}
		else
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	dongle->is_available = 0;
	ft_heap_pop(dongle);
	pthread_mutex_unlock(&dongle->mutex);
}

static void	ft_unlock_dongle(t_simulation *simulation, int index)
{
	t_dongle	*dongle;

	dongle = &simulation->dongles[index];
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_available = 0;
	dongle->availability_time = ft_get_current_time_in_ms()
		+ simulation->data->dongle_cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

void   ft_release_dongle(t_coder *coder)
{
    t_simulation    *simulation;
    
    simulation = coder->simulation;
    ft_unlock_dongle(simulation, coder->left_dongle);
    ft_unlock_dongle(simulation, coder->right_dongle);
}

void   ft_acquire_dongle(t_coder *coder)
{
    int            left_index;
    int            right_index;

    left_index = coder->left_dongle;
    right_index = coder->right_dongle;
	if (left_index == right_index)
	{
		ft_lock_dongle(coder, left_index);
		return ;
	}
    ft_lock_dongle(coder, ft_get_min(left_index, right_index));
    ft_lock_dongle(coder, ft_get_max(left_index, right_index));
}

static int	ft_can_acquire_both(t_coder *coder)
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