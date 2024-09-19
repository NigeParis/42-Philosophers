/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:42:34 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/19 19:52:27 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int make_threads(t_input_args *args)
{
    int i;

    // if (pthread_create(&args->handler, NULL, &monitor, args))
    //     return (EXIT_FAILURE);
    i = 0;
    
    args->start_thread = get_timestamp();
    while (i < args->nbr_philo)
    {
        args->philo[i].id = i + 1;
        args->philo[i].args = args;
        if (pthread_create(&args->philo[i].thread, NULL, &thread, &args->philo[i]))
            return (EXIT_FAILURE);
        i++;
    }

    monitor(args);
    
    i = 0;
    while (i < args->nbr_philo)
    {
        if (pthread_join(args->philo[i].thread, NULL))
            return (EXIT_FAILURE);
        i++;
    }
    // if (pthread_join(args->handler, NULL))
    //     return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}


