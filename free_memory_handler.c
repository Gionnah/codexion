/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 21:46:12 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 13:28:15 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_memory.h"

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
    int n_coder;

    n_coder = simulation->data->number_of_coders;
	pthread_mutex_destroy(&simulation->simulation_stop_mutex);
	pthread_mutex_destroy(&simulation->simulation_log_mutex);
    pthread_mutex_destroy(&simulation->simulation_state_mutex);
    free(simulation->coders);
    ft_free_dongle(simulation->dongles, n_coder);
    free(simulation->dongles);
    free(simulation);
}

void    *ft_free_simulation_issues(t_simulation **simulation)
{
    pthread_mutex_destroy(&(*simulation)->simulation_state_mutex);
    pthread_mutex_destroy(&(*simulation)->simulation_stop_mutex);
    free(*simulation);
    *simulation = NULL;
    return (NULL);
}
