/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_action_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 00:22:47 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 00:23:09 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long    ft_get_current_time_in_ms(void)
{
    struct timeval  tv;
    long            milliseconds;

    gettimeofday(&tv, NULL);
    milliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (milliseconds);
}