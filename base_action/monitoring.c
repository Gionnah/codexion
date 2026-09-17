/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 00:38:00 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 21:35:34 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static int	ft_coder_burned_out(t_coder *coder, long now)
{
	t_simulation	*simulation;
	long			start;
	long			deadline;

	simulation = coder->simulation;
	pthread_mutex_lock(&simulation->simulation_state_mutex);
	start = coder->last_compile_start;
	pthread_mutex_unlock(&simulation->simulation_state_mutex);
	if (start == 0)
		start = simulation->simulation_start_time;
	deadline = start + simulation->data->time_to_burnout;
	return (now >= deadline);
}

void	*ft_monitor_routine(void *arg)
{
	t_simulation	*simulation;
	long			now;
	int				i;

	simulation = (t_simulation *)arg;
	while (!ft_is_simulation_stopped(simulation))
	{
		now = ft_get_current_time_in_ms();
		i = 0;
		while (i < simulation->data->number_of_coders)
		{
			if (ft_coder_burned_out(&simulation->coders[i], now))
			{
				ft_set_simulation_stopped(simulation);
				ft_log_state(&simulation->coders[i], "burned out");
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
