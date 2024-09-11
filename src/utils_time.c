/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:48:56 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/04 10:51:56 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    time_diff(t_input_args args, struct timeval current_time)
{
    long    time_diff;

    time_diff = 0; 
	gettimeofday(&current_time, NULL);
    time_diff = ((current_time.tv_sec * 1000) - (args.start_time_sec * 1000));
    time_diff += ((current_time.tv_usec - args.start_time_usec) / 1000);
    return (time_diff);
}