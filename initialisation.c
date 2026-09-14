/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 09:59:06 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/14 12:46:38 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_simulation	*ft_init_simulation(t_data *data)
{
	t_simulation	*simulation;

	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	simulation->data = data;
	simulation->coders = NULL;
	simulation->dongles = NULL;
	simulation->is_simulation_stopped = 0;
	simulation->simulation_start_time = 0;
	if (pthread_mutex_init(&simulation->simulation_stop_mutex, NULL))
	{
		free(simulation);
		return (NULL);
	}
	if (pthread_mutex_init(&simulation->simulation_log_mutex, NULL))
	{
		pthread_mutex_destroy(&simulation->simulation_stop_mutex);
		free(simulation);
		return (NULL);
	}
	return (simulation);
}

int	ft_init_coders(t_simulation *simulation)
{
	int	i;
	int	n;

	n = simulation->data->number_of_coders;
	simulation->coders = malloc(sizeof(t_coder) * n);
	if (!simulation->coders)
		return (1);
	i = 0;
	while (i < n)
	{
		simulation->coders[i].id = i + 1;
		simulation->coders[i].last_compile_start = 0;
		simulation->coders[i].compile_count = 0;
		simulation->coders[i].left_dongle = i;
		simulation->coders[i].right_dongle = (i + n - 1) % n;
		simulation->coders[i].simulation = simulation;
		i++;
	}
	return (0);
}

int	ft_init_dongles(t_simulation *simulation)
{
	int	iterator;
	int	n_coders;

	iterator = 0;
	n_coders = simulation->data->number_of_coders;
	simulation->dongles = malloc(sizeof(t_dongle) * n_coders);
	if (!simulation->dongles)
		return (1);
	while (iterator < n_coders)
	{
		simulation->dongles[iterator].is_available = 1;
		if (pthread_mutex_init(&simulation->dongles[iterator].mutex, NULL))
			return (1);
		iterator++;
	}
	return (0);
}
