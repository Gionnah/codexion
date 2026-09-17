/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 21:46:12 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 22:25:33 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../free_memory.h"

void    ft_free_dongle(t_dongle *dongle, int n_coder)
{
    int i;

    i = 0;
    while (i < n_coder)
    {
        free(dongle[i].queue);
		pthread_mutex_destroy(&dongle[i].mutex);
		pthread_cond_destroy(&dongle[i].cond);
        i++;
    }
}

void	ft_free_simulation(t_simulation *simulation)
{
	int	n_coder;

	if (!simulation)
		return ;
	n_coder = simulation->data->number_of_coders;
	pthread_mutex_destroy(&simulation->simulation_stop_mutex);
	pthread_mutex_destroy(&simulation->simulation_log_mutex);
	pthread_mutex_destroy(&simulation->simulation_state_mutex);
	pthread_mutex_destroy(&simulation->scheduler_mutex);
	pthread_cond_destroy(&simulation->scheduler_cond);
	free(simulation->coders);
	if (simulation->dongles)
	{
		ft_free_dongle(simulation->dongles, n_coder);
		free(simulation->dongles);
	}
	free(simulation);
}

void	*ft_free_simulation_issues(t_simulation **simulation)
{
	free(*simulation);
	*simulation = NULL;
	return (NULL);
}

void	ft_free_dongles_init(t_dongle *dongles, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(dongles[i].queue);
		pthread_mutex_destroy(&dongles[i].mutex);
		pthread_cond_destroy(&dongles[i].cond);
		i++;
	}
	free(dongles);
}
