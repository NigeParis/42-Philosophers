/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:42:34 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/23 19:34:32 by nrobinso         ###   ########.fr       */
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
        i++;
    }
    // DEBUG_print_input(args, args->philo, 0);
    
    monitor(args);
    i = 0;
    while (i < args->nbr_philo)
    {
        pthread_join(args->philo[i].thread, NULL);
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
    if ((philo->id + 1) % 2 == 0)
    while (1)
    { 
        philo_eating(philo);
        if (end_all(args))
            break ;
        philo_sleeping(philo);
        if (end_all(args))
            break ;
        philo_thinking(philo);
        if (end_all(args))
            break ;
    }
    return (EXIT_SUCCESS);    
}

int philo_eating(t_current_philo *philo)
{
    int fork_a;
    int fork_b;

    fork_a = philo->id;
    fork_b = (philo->id + 1) % philo->args->nbr_forks;

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->args->fork[fork_a]);
        put_log(philo, "has taken a fork");
        usleep(100); // Ajout d'un léger délai pour éviter les interblocages
        pthread_mutex_lock(&philo->args->fork[fork_b]);
        put_log(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->args->fork[fork_b]);
        put_log(philo, "has taken a fork");
        usleep(100); // Ajout d'un léger délai pour éviter les interblocages
        pthread_mutex_lock(&philo->args->fork[fork_a]);
        put_log(philo, "has taken a fork");
    }

    put_log(philo, "is eating");
    pthread_mutex_lock(&philo->args->meal);
    philo->nbr_meals++;
    philo->last_meal = get_timestamp();
    if ((philo->args->nbr_repas > 0) && (philo->nbr_meals >= philo->args->nbr_repas))
        philo->is_full = 1;
    pthread_mutex_unlock(&philo->args->meal);

    ft_sleep((long long)philo->args->time_to_eat, philo->args);

    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(&philo->args->fork[fork_a]);
        usleep(100);
        pthread_mutex_unlock(&philo->args->fork[fork_b]);
    }
    else
    {
        pthread_mutex_unlock(&philo->args->fork[fork_b]);
        usleep(100);
        pthread_mutex_unlock(&philo->args->fork[fork_a]);
    }

    return (EXIT_SUCCESS);
}




int    philo_sleeping(t_current_philo *philo)
{
    put_log(philo, "is sleeping");
    ft_sleep((long long)philo->args->time_to_sleep, philo->args);
    return (EXIT_SUCCESS);
}

int philo_thinking(t_current_philo *philo)
{
    put_log(philo, "is thinking");
    if ((philo->args->nbr_philo % 2) != 0)
        usleep(1);
    return (EXIT_SUCCESS);
}
