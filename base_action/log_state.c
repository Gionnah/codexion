/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 21:18:44 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 21:35:50 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	ft_log_state(t_coder *coder, char *state)
{
	t_simulation	*simulation;
	long			time;

	simulation = coder->simulation;
	time = ft_get_current_time_in_ms()
		- simulation->simulation_start_time;
	pthread_mutex_lock(&simulation->simulation_log_mutex);
	fprintf(stderr, "%ld %d %s\n", time, coder->id, state);
	pthread_mutex_unlock(&simulation->simulation_log_mutex);
}