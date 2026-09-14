/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 00:38:00 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 00:44:16 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	ft_coder_burned_out(t_coder *coder, long now)
{
	long	start;
	long	deadline;

	start = coder->last_compile_start;
	if (start == 0)
		start = coder->simulation->simulation_start_time;
	deadline = start + coder->simulation->data->time_to_burnout;
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
				fprintf(stderr, "coder %d burned out\n",
					simulation->coders[i].id);
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
