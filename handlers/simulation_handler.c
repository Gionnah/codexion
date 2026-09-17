/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 21:30:50 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 22:28:11 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"
#include "../free_memory.h"

static int	ft_init_all(t_simulation **simulation, t_data *args)
{
	*simulation = ft_init_simulation(args);
	if (!*simulation)
		return (1);
	if (ft_init_coders(*simulation))
	{
		ft_free_simulation(*simulation);
		*simulation = NULL;
		return (1);
	}
	if (ft_init_dongles(*simulation))
	{
		ft_free_simulation(*simulation);
		*simulation = NULL;
		return (1);
	}
	return (0);
}

static int	ft_start_threads(t_simulation *simulation)
{
	simulation->simulation_start_time = ft_get_current_time_in_ms();
	if (pthread_create(&simulation->monitor_thread, NULL,
			ft_monitor_routine, simulation))
		return (1);
	if (ft_create_coder_threads(simulation))
		return (1);
	if (ft_join_coder_threads(simulation))
		return (1);
	if (pthread_join(simulation->monitor_thread, NULL))
		return (1);
	return (0);
}

int	ft_start_simulation(t_simulation **simulation, t_data *args)
{
	if (ft_init_all(simulation, args))
		return (1);
	if (ft_start_threads(*simulation))
		return (1);
	return (0);
}
