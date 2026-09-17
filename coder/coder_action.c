/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 23:59:25 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/17 21:35:00 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	ft_compile(t_coder *coder)
{
	t_simulation	*simulation;

	simulation = coder->simulation;
	pthread_mutex_lock(&simulation->simulation_state_mutex);
	coder->last_compile_start = ft_get_current_time_in_ms();
	pthread_mutex_unlock(&simulation->simulation_state_mutex);
	ft_log_state(coder, "is compiling");
	usleep(coder->simulation->data->time_to_compile * 1000);
	pthread_mutex_lock(&coder->simulation->simulation_state_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->simulation->simulation_state_mutex);
	if (ft_all_coders_finished(coder->simulation))
		ft_set_simulation_stopped(coder->simulation);
}

void	ft_debug(t_coder *coder)
{
	ft_log_state(coder, "is debugging");
	usleep(coder->simulation->data->time_to_debug * 1000);
}

void	ft_refactor(t_coder *coder)
{
	ft_log_state(coder, "is refactoring");
	usleep(coder->simulation->data->time_to_refactor * 1000);
}
