/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 21:30:50 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 00:47:35 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int ft_start_simulation(t_simulation **simulation, t_data *args)
{
    *simulation = ft_init_simulation(args);
	if (!*simulation)
		return (1);
	if (ft_init_coders(*simulation))
		return (1);
	if (ft_init_dongles(*simulation))
		return (1);
	(*simulation)->simulation_start_time = ft_get_current_time_in_ms();
	pthread_create(&(*simulation)->monitor_thread, NULL, ft_monitor_routine, *simulation);
	if (ft_create_coder_threads(*simulation))
		return (1);
	if (ft_join_coder_threads(*simulation))
		return (1);
	pthread_join((*simulation)->monitor_thread, NULL);
    return (0);
}
