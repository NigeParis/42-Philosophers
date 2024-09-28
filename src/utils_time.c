/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:48:56 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/28 10:36:58 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	struct timeval	time_now;
	long long		time_stamp;

	gettimeofday(&time_now, NULL);
	time_stamp = ((time_now.tv_sec * 1000LL) + (time_now.tv_usec / 1000));
	return (time_stamp);
}

void	ft_sleep(long long wait)
{
	long long	sleep_time;

	sleep_time = get_timestamp() + wait;
	while (get_timestamp() < sleep_time)
		usleep(10);
}
