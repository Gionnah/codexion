/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 23:16:32 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 12:25:50 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "free_memory.h"

static void	ft_lock_dongle(t_simulation *simulation, int index)
{
	t_dongle        *dongle;
	struct timespec timeout;

	dongle = &simulation->dongles[index];
	pthread_mutex_lock(&dongle->mutex);
	while (!dongle->is_available)
	{
		timeout = ft_get_timeout(dongle->availability_time);
		pthread_cond_timedwait(&dongle->cond,
			&dongle->mutex, &timeout);
		if (ft_get_current_time_in_ms() >= dongle->availability_time)
			dongle->is_available = 1;
	}
	dongle->is_available = 0;
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
	pthread_cond_signal(&dongle->cond);
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
    t_simulation    *simulation;
    int            left_index;
    int            right_index;
    
    simulation = coder->simulation;
    left_index = coder->left_dongle;
    right_index = coder->right_dongle;

    ft_lock_dongle(simulation, ft_get_min(left_index, right_index));
    ft_lock_dongle(simulation, ft_get_max(left_index, right_index));
}