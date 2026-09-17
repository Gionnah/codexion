/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 09:59:06 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 22:49:03 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"
#include "../free_memory.h"

t_simulation	*ft_init_simulation(t_data *data)
{
	t_simulation	*simulation;

	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	simulation->data = data;
	simulation->is_simulation_stopped = 0;
	simulation->queue_order = 0;
	if (ft_init_scheduler(simulation))
		return (free(simulation), NULL);
	if (ft_init_mutexes(simulation))
	{
		pthread_cond_destroy(&simulation->scheduler_cond);
		pthread_mutex_destroy(&simulation->scheduler_mutex);
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

static int	ft_init_dongle(t_dongle *dongle, int n_cdr)
{
	dongle->is_available = 1;
	dongle->availability_time = 0;
	dongle->queue_size = 0;
	dongle->queue = malloc(sizeof(t_queues) * n_cdr);
	if (!dongle->queue)
		return (1);
	if (pthread_mutex_init(&dongle->mutex, NULL))
	{
		free(dongle->queue);
		return (1);
	}
	if (pthread_cond_init(&dongle->cond, NULL))
	{
		pthread_mutex_destroy(&dongle->mutex);
		free(dongle->queue);
		return (1);
	}
	return (0);
}

int	ft_init_dongles(t_simulation *simulation)
{
	int	i;
	int	n_cdr;

	n_cdr = simulation->data->number_of_coders;
	simulation->dongles = malloc(sizeof(t_dongle) * n_cdr);
	if (!simulation->dongles)
		return (1);
	i = 0;
	while (i < n_cdr)
	{
		if (ft_init_dongle(&simulation->dongles[i], n_cdr))
		{
			ft_free_dongles_init(simulation->dongles, i);
			return (1);
		}
		i++;
	}
	return (0);
}
