/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 11:57:50 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/15 12:11:42 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

struct timespec	ft_get_timeout(long availability_time)
{
    struct timespec  timeout;

    timeout.tv_sec = availability_time / 1000;
    timeout.tv_nsec = (availability_time % 1000) * 1000000;
    return (timeout);
}

int ft_get_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

int ft_get_max(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}