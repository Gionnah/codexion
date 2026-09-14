/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelonja <mvelonja@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 23:16:32 by mvelonja          #+#    #+#             */
/*   Updated: 2026/09/14 23:55:04 by mvelonja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void    ft_lock_dongle(t_simulation *simulation, int index)
{
    pthread_mutex_lock(&simulation->dongles[index].mutex);    
    while (!simulation->dongles[index].is_available)
        pthread_cond_wait(&simulation->dongles[index].cond,
            &simulation->dongles[index].mutex);
    simulation->dongles[index].is_available = 0;
    pthread_mutex_unlock(&simulation->dongles[index].mutex);
}

static void    ft_unlock_dongle(t_simulation *simulation, int index)
{
    pthread_mutex_lock(&simulation->dongles[index].mutex);
    simulation->dongles[index].is_available = 1;
    pthread_cond_signal(&simulation->dongles[index].cond);
    pthread_mutex_unlock(&simulation->dongles[index].mutex);
}

void   ft_release_dongle(t_coder *coder)
{
    t_simulation    *simulation;
    
    simulation = coder->simulation;
    ft_unlock_dongle(simulation, coder->left_dongle);
    ft_unlock_dongle(simulation, coder->right_dongle);
}

void   ft_acquire_dongle(t_coder *coder)
{
    t_simulation    *simulation;
    int            left_index;
    int            right_index;
    
    simulation = coder->simulation;
    left_index = coder->left_dongle;
    right_index = coder->right_dongle;
    ft_lock_dongle(simulation, coder->left_dongle);    
    ft_lock_dongle(simulation, coder->right_dongle);    
}