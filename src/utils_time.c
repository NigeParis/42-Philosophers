/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:48:56 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/26 13:06:26 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	struct timeval	current_time;
	long long		time_stamp;

	gettimeofday(&current_time, NULL);
	time_stamp = ((current_time.tv_sec * 1000LL) + (current_time.tv_usec / 1000));
	return (time_stamp);
}

void	ft_sleep(long long wait, t_input_args *args)
{
	long long	sleep_time;

	(void)args;
	sleep_time = get_timestamp() + wait;
	while (get_timestamp() < sleep_time)
		usleep(2);
}
