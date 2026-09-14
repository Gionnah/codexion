/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_handler_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 05:47:44 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 00:06:59 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int ft_is_simulation_stopped(t_simulation *simulation)
{
	int is_stopped;

	pthread_mutex_lock(&simulation->simulation_stop_mutex);
	is_stopped = simulation->is_simulation_stopped;
	pthread_mutex_unlock(&simulation->simulation_stop_mutex);
	return (is_stopped);
}

int ft_set_simulation_stopped(t_simulation *simulation)
{
    pthread_mutex_lock(&simulation->simulation_stop_mutex);
    simulation->is_simulation_stopped = 1;
    pthread_mutex_unlock(&simulation->simulation_stop_mutex);
    return (0);
}

int	ft_all_coders_finished(t_simulation *simulation)
{
	int	i;
	int	required;

	required = simulation->data->time_of_compiles_required;
	i = 0;
	while (i < simulation->data->number_of_coders)
	{
		if (simulation->coders[i].compile_count < required)
			return (0);
		i++;
	}
	return (1);
}
