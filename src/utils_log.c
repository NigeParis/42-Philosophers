/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:26:44 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/21 16:28:52 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    put_log(t_current_philo *philo, char *str)
{
    long long int stamp;
    int      id;
    pthread_mutex_lock(&philo->args->log); 
    id = philo->id;
    pthread_mutex_unlock(&philo->args->log); 
    

    pthread_mutex_lock(&philo->args->log); 
    stamp = (get_timestamp() - philo->args->start_thread);
    
    printf("%llu ms philo[%d] %s\n", stamp, id, str);
    pthread_mutex_unlock(&philo->args->log); 
}

void    put_death_log(t_current_philo *philo, char *str)
{
    long long int stamp;
    int      id;
    pthread_mutex_lock(&philo->args->log); 
    id = philo->id;
    pthread_mutex_unlock(&philo->args->log); 

    pthread_mutex_lock(&philo->args->log); 
    stamp = get_timestamp() - ((philo[philo->id].last_meal \
    - philo->args->time_to_die));
    printf("%lld ms philo[%d] %s\n", stamp, id, str);
    pthread_mutex_unlock(&philo->args->log); 
}

