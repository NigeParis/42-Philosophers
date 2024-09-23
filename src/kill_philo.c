/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:33:25 by nige42            #+#    #+#             */
/*   Updated: 2024/09/23 17:16:00 by nrobinso         ###   ########.fr       */
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
    pthread_mutex_lock(&args->meal);
    while (i < args->nbr_philo)
    {
        // if (life_time_left(args, i) < 0)
        if (args->time_to_die < (get_timestamp() - args->philo[i].last_meal))
        {
            set_end_all(args);
            args->stop_thread = get_timestamp();
            put_death_log(&args->philo[i], "died");

            pthread_mutex_unlock(&args->meal); 
            return (1);
        }
        i++;
    }
    pthread_mutex_unlock(&args->meal); 
    return (0);
}

int philo_all_full(t_current_philo *philo)
{
    int i;
    int eaten_all_meals;

    i = 0;
    eaten_all_meals = 0;
    while (i < philo->args->nbr_philo)
    {
        pthread_mutex_lock(&philo->args->meal); 
        if ((philo->args)->philo[i].is_full) {
            eaten_all_meals++;
        }
        pthread_mutex_unlock(&philo->args->meal); 
        i++;
    }
    pthread_mutex_lock(&philo->args->meal); 
    if (eaten_all_meals >= philo->args->nbr_philo)
    {
     
        pthread_mutex_lock(&philo->args->death); 
        philo->args->stop = 2;
        pthread_mutex_unlock(&philo->args->death); 
        
        pthread_mutex_unlock(&philo->args->meal); 
           return (1);
    }
    pthread_mutex_unlock(&philo->args->meal); 
    return (0);
}