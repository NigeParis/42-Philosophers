/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:33:25 by nige42            #+#    #+#             */
/*   Updated: 2024/09/21 16:42:35 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int end_all(t_input_args *args)
{
    int signal;

    signal = 0;
    pthread_mutex_lock(&args->death); 
    signal = args->stop;
    pthread_mutex_unlock(&args->death); 
    return (signal);
}

int set_end_all(t_input_args *args)
{
    pthread_mutex_lock(&args->death); 
    args->stop = 1;
    pthread_mutex_unlock(&args->death); 
    return (EXIT_SUCCESS);
}

int philo_is_dead(t_input_args *args)
{
    int i;

    i = 0;
    if (!args)
        return (printf("error pas args\n") ,EXIT_FAILURE);
    if (end_all(args))
        return (1);
    while (i < args->nbr_philo)
    {

        pthread_mutex_lock(&args->meal);
        if (eat_time_left(args, i) < 0)
        {
            put_death_log(&args->philo[i], "died");
            set_end_all(args);
            


            pthread_mutex_unlock(&args->meal); 
            return (1);
        }
        pthread_mutex_unlock(&args->meal); 
        i++;
    }
    return (0);
}

int check_death(t_input_args *args)
{
    if (!args)
        return (EXIT_FAILURE);
        
    if (philo_is_dead(args))
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}
