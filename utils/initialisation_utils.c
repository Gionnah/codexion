/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 22:19:25 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 22:59:41 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	ft_init_scheduler(t_simulation *simulation)
{
	if (pthread_mutex_init(&simulation->scheduler_mutex, NULL))
		return (1);
	if (pthread_cond_init(&simulation->scheduler_cond, NULL))
	{
		pthread_mutex_destroy(&simulation->scheduler_mutex);
		return (1);
	}
	return (0);
}

int	ft_init_mutexes(t_simulation *simulation)
{
	if (pthread_mutex_init(&simulation->simulation_state_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&simulation->simulation_stop_mutex, NULL))
	{
		pthread_mutex_destroy(&simulation->simulation_state_mutex);
		return (1);
	}
	if (pthread_mutex_init(&simulation->simulation_log_mutex, NULL))
	{
		pthread_mutex_destroy(&simulation->simulation_stop_mutex);
		pthread_mutex_destroy(&simulation->simulation_state_mutex);
		return (1);
	}
	return (0);
}
