/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 22:43:32 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/10 16:27:41 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_is_valid_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 9)
		return (0);
	while (i < 7)
	{
		if (!ft_is_integer_value(av[i++]))
			return (0);
	}
	if (ft_strcmp("fifo", av[7]) && ft_strcmp("edf", av[7]))
		return (0);
	return (1);
}

t_data	*ft_get_arg_value(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->number_of_coders = ft_atoi(av[0]);
	data->time_to_burnout = ft_atoi(av[1]);
	data->time_to_compile = ft_atoi(av[2]);
	data->time_to_debug = ft_atoi(av[3]);
	data->time_to_refactor = ft_atoi(av[4]);
	data->time_of_compiles_required = ft_atoi(av[5]);
	data->dongle_cooldown = ft_atoi(av[6]);
	data->scheduler = av[7];
	return (data);
}
