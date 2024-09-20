/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:48:56 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/20 09:11:15 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long    get_timestamp()
{
    struct timeval current_time;
    long    time_stamp;
    
    gettimeofday(&current_time, NULL);
    time_stamp = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
    return (time_stamp);
}

long    start_philo_timer(t_input_args *args, long waitime)
{
    long  time;
    
    time = args->start_thread + waitime;   
    while (get_timestamp() < time)
    {
        usleep(500);
    }

    return(time);
}