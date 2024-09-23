/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:48:56 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/23 11:23:26 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long long   get_timestamp(void)
{
    struct timeval current_time;
    long long   time_stamp;
    
    gettimeofday(&current_time, NULL);
    time_stamp = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
    return (time_stamp);
}

void    start_philo_timer(long waitime)
{
    while (get_timestamp() < waitime)
    {
        continue ;
    }
}

void    ft_sleep(long long wait, t_input_args *args)
{
    long long sleep_time;

    sleep_time = get_timestamp() + wait;
    while (!end_all(args) && get_timestamp() < sleep_time)
        usleep(50);   
}


