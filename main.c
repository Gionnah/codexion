/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 22:59:57 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/12 05:05:04 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "free_memory.h"

int	main(int argc, char **argv)
{
    t_data *args;
    t_simulation *simulation;
    
	if (!ft_is_valid_args(argc, ++argv))
	{
		write(2, "ERROR INVALID ARGUMENTS.\n", 26);
		return (1);
	}
    args = ft_get_arg_value(argv);
	ft_start_simulation(&simulation, args);
	ft_free_simulation(simulation);
    free(args);
	return (0);
}
