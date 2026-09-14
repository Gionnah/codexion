/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 16:46:11 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/14 12:46:55 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*ft_coder_routine(void *arg)
{
	t_coder			*coder;
	t_simulation	*simulation;

	coder = (t_coder *)arg;
	simulation = coder->simulation;
	printf("coder %d started\n", coder->id);
	printf("stopped = %d\n", ft_is_simulation_stopped(simulation));
	return (NULL);
}

int	ft_create_coder_threads(t_simulation *simulation)
{
	int	i;
	int	n;

	n = simulation->data->number_of_coders;
	i = 0;
	while (i < n)
	{
		if (pthread_create(&simulation->coders[i].thread, NULL,
				ft_coder_routine, &simulation->coders[i]) != 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_join_coder_threads(t_simulation *simulation)
{
	int	i;
	int	n;

	n = simulation->data->number_of_coders;
	i = 0;
	while (i < n)
	{
		if (pthread_join(simulation->coders[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
