/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:42:34 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/20 23:56:31 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int make_threads(t_input_args *args)
{
    int i;
    
    i = 0;
    while (i < args->nbr_philo)
    {
        if (pthread_create(&args->philo[i].thread, \
        NULL, &thread, &args->philo[i]))
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

void *thread(void *thread_philo)
{
    t_current_philo *philo;
    t_input_args *args;

    if (!thread_philo)
        return (NULL);
    philo = (t_current_philo *)thread_philo;
    args = philo->args;
    start_philo_timer(args->start_thread); 
    while (!end_all(args))
    {
        philo_eating(philo);
        philo_sleeping(philo);
        philo_thinking(philo);
    }
    return (EXIT_SUCCESS);    
}

int    philo_eating(t_current_philo *philo)
{
    if (!philo)
        return (set_end_all(philo->args), EXIT_FAILURE);
    put_log(philo, "is eating");
    pthread_mutex_lock(&philo->args->meal); 
    philo->nbr_meals++;
    philo->last_meal = get_timestamp();
    ft_sleep((long long)philo->args->time_to_eat, philo->args);
    pthread_mutex_unlock(&philo->args->meal);  
    return (EXIT_SUCCESS);
}

int    philo_sleeping(t_current_philo *philo)
{
    if (!philo)
        return (set_end_all(philo->args),EXIT_FAILURE);
    put_log(philo, "is sleeping");
    ft_sleep((long long)philo->args->time_to_sleep, philo->args);
    return (EXIT_SUCCESS);
}

int philo_thinking(t_current_philo *philo)
{
    if (!philo)
        return (set_end_all(philo->args),EXIT_FAILURE);
    put_log(philo, "is thinking");
    return (EXIT_SUCCESS);
}
