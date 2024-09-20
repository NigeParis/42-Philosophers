/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:26:44 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/20 13:07:46 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    put_log(t_current_philo *philo, char *str)
{
    long long int stamp;
    int      id;

    pthread_mutex_lock(&philo->args->meal); 
    id = philo->id;
    pthread_mutex_unlock(&philo->args->meal); 
    

    stamp = (get_timestamp() - philo->args->start_thread);
    
    pthread_mutex_lock(&philo->args->log); 
    printf("%llu ms philo[%d] %s\n", stamp, id, str);
    pthread_mutex_unlock(&philo->args->log); 
}

