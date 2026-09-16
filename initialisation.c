/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanitriniala <hanitriniala@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 09:59:06 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 22:08:43 by hanitrinial      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "free_memory.h"

t_simulation	*ft_init_simulation(t_data *data)
{
	t_simulation	*simulation;
	int				have_issue;

	have_issue = 0;
	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	simulation->data = data;
	simulation->is_simulation_stopped = 0;
	simulation->queue_order = 0;
	pthread_mutex_init(&simulation->scheduler_mutex, NULL);
	pthread_cond_init(&simulation->scheduler_cond, NULL);
	if (pthread_mutex_init(&simulation->simulation_state_mutex, NULL))
		have_issue = 1;
	if (pthread_mutex_init(&simulation->simulation_stop_mutex, NULL))
	{
		pthread_mutex_destroy(&simulation->simulation_state_mutex);
		have_issue = 1;
	}
	if (pthread_mutex_init(&simulation->simulation_log_mutex, NULL))
		have_issue = 1;
	if (have_issue)
		ft_free_simulation_issues(&simulation);
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
	int	n_cdr;

	iterator = 0;
	n_cdr = simulation->data->number_of_coders;
	simulation->dongles = malloc(sizeof(t_dongle) * n_cdr);
	if (!simulation->dongles)
		return (1);
	while (iterator < n_cdr)
	{
		simulation->dongles[iterator].is_available = 1;
		simulation->dongles[iterator].availability_time = 0;
		simulation->dongles[iterator].queue = malloc(sizeof(t_queues) * n_cdr);
		if (!simulation->dongles[iterator].queue)
			return (1);
		simulation->dongles[iterator].queue_size = 0;
		if (pthread_mutex_init(&simulation->dongles[iterator].mutex, NULL))
			return (1);
		if (pthread_cond_init(&simulation->dongles[iterator].cond, NULL))
		{
			pthread_mutex_destroy(&simulation->dongles[iterator].mutex);
			return (1);
		}
		iterator++;
	}
	return (0);
}
