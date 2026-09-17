/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_handler_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 05:47:44 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 21:34:07 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	ft_is_simulation_stopped(t_simulation *simulation)
{
	int	is_stopped;

	pthread_mutex_lock(&simulation->scheduler_mutex);
	is_stopped = simulation->is_simulation_stopped;
	pthread_mutex_unlock(&simulation->scheduler_mutex);
	return (is_stopped);
}

int	ft_set_simulation_stopped(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->scheduler_mutex);
	simulation->is_simulation_stopped = 1;
	pthread_cond_broadcast(&simulation->scheduler_cond);
	pthread_mutex_unlock(&simulation->scheduler_mutex);
	return (0);
}

int	ft_all_coders_finished(t_simulation *simulation)
{
	int	i;
	int	required;

	required = simulation->data->time_of_compiles_required;
	pthread_mutex_lock(&simulation->simulation_state_mutex);
	i = 0;
	while (i < simulation->data->number_of_coders)
	{
		if (simulation->coders[i].compile_count < required)
		{
			pthread_mutex_unlock(&simulation->simulation_state_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&simulation->simulation_state_mutex);
	return (1);
}

void	ft_update_dongle(t_dongle *dongle, long now)
{
	if (!dongle->is_available && now >= dongle->availability_time)
		dongle->is_available = 1;
}

void	ft_update_dongles(t_simulation *simulation)
{
	int		i;
	long	now;

	i = 0;
	now = ft_get_current_time_in_ms();
	while (i < simulation->data->number_of_coders)
	{
		if (!simulation->dongles[i].is_available
			&& now >= simulation->dongles[i].availability_time)
			simulation->dongles[i].is_available = 1;
		i++;
	}
}
