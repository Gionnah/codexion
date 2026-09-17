/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_queue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 19:06:29 by hanitrinial       #+#    #+#             */
/*   Updated: 2026/09/17 20:37:10 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ft_add_request(t_coder *coder, t_queues *request)
{
	t_simulation	*simulation;

	simulation = coder->simulation;
	ft_heap_push(&simulation->dongles[coder->left_dongle], *request);
	if (coder->left_dongle != coder->right_dongle)
		ft_heap_push(&simulation->dongles[coder->right_dongle], *request);
}

void	ft_remove_request(t_coder *coder)
{
	t_simulation	*simulation;

	simulation = coder->simulation;
	ft_heap_pop(&simulation->dongles[coder->left_dongle]);
	if (coder->left_dongle != coder->right_dongle)
		ft_heap_pop(&simulation->dongles[coder->right_dongle]);
}
