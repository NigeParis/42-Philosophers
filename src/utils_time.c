/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:48:56 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/13 10:08:32 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    time_diff(t_input_args *args, struct timeval current_time, int i)
{
    long    time_diff;
   

    time_diff = 0; 
	gettimeofday(&current_time, NULL);
    time_diff = (((current_time.tv_sec * 1000) \
    + (current_time.tv_usec / 1000)) - (args->philo[i].start_time));

    return (time_diff);
}

long total_time(t_input_args *args, struct timeval *current_time)
{
    
    long    total_time;
    long    time;
    int i;
    
    i = 0;
    
    total_time = 0;
    while (i < args->nbr_philo)
    {
    
        time = time_diff(args, *current_time, i);    
        if (total_time < time)
            total_time = time;
        i++;
    }
    return (total_time);
}

long    get_timestamp(struct timeval *current_time)
{
    long    time_stamp;
    
    gettimeofday(current_time, NULL);
    time_stamp = ((current_time->tv_sec * 1000) + (current_time->tv_usec / 1000));
    return (time_stamp);
}

