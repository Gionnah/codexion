/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 23:59:25 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 00:02:37 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ft_compile(t_coder *coder)
{
	fprintf(stderr, "coder %d compiling\n", coder->id);
	usleep(coder->simulation->data->time_to_compile * 1000);
	coder->compile_count++;
}

void	ft_debug(t_coder *coder)
{
	fprintf(stderr, "coder %d debugging\n", coder->id);
	usleep(coder->simulation->data->time_to_debug * 1000);
}

void	ft_refactor(t_coder *coder)
{
	fprintf(stderr, "coder %d refactoring\n", coder->id);
	usleep(coder->simulation->data->time_to_refactor * 1000);
}
