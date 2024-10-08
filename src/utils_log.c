/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:26:44 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/27 11:10:21 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_log(t_current_philo *philo, char *str)
{
	long long int	stamp;
	int				id;

	pthread_mutex_lock(&philo->args->log);
	id = philo->id;
	stamp = (get_timestamp() - philo->args->start_time);
	pthread_mutex_lock(&philo->args->death);
	if (philo->args->stop != 2)
		printf("%llu %d %s\n", stamp, id + 1, str);
	pthread_mutex_unlock(&philo->args->death);
	pthread_mutex_unlock(&philo->args->log);
}

void	put_death_log(t_current_philo *philo, char *str)
{
	long long int	stamp;
	int				id;

	pthread_mutex_lock(&philo->args->log);
	id = philo->id;
	stamp = (get_timestamp() - philo->args->start_time);
	pthread_mutex_lock(&philo->args->death);
	philo->args->stop = 2;
	pthread_mutex_unlock(&philo->args->death);
	printf("%lld %d %s\n", stamp, id + 1, str);
	pthread_mutex_unlock(&philo->args->log);
}

void	put_are_full_log(t_current_philo *philo, char *str)
{
	long long int	stamp;

	pthread_mutex_lock(&philo->args->log);
	stamp = (get_timestamp() - philo->args->start_time) \
	+ (philo->args->time_to_eat);
	printf("%llu all philos %s\n", stamp, str);
	usleep(10);
	pthread_mutex_unlock(&philo->args->log);
}
