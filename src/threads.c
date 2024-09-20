/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:42:34 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/20 12:32:30 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int make_threads(t_input_args *args)
{
    int i;
    
    i = 0;
    while (i < args->nbr_philo)
    {

        if (pthread_create(&args->philo[i].thread, NULL, &thread, &args->philo[i]))
            return (EXIT_FAILURE);
       
        usleep(10);
        i++;
    }
    print_input(args, args->philo, 0);
    monitor(args);
    
    i = 0;
    while (i < args->nbr_philo)
    {
        if (pthread_join(args->philo[i].thread, NULL))
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}


