/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:26:44 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/24 22:30:07 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_log(t_current_philo *philo, char *str)
{
	long long int	stamp;
	int				id;

	pthread_mutex_lock(&philo->args->log);
	id = philo->id;
	stamp = (get_timestamp() - philo->args->start_thread);
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
	stamp = (get_timestamp() - philo->args->start_thread);
	pthread_mutex_lock(&philo->args->death);
	philo->args->stop = 2;
	pthread_mutex_unlock(&philo->args->death);
	printf(RED);
	printf("%lld %d %s\n", stamp, id, str);
	printf(RESET);
	pthread_mutex_unlock(&philo->args->log);
}

void	put_are_full_log(t_current_philo *philo, char *str)
{
	long long int	stamp;

	pthread_mutex_lock(&philo->args->log);
	stamp = (get_timestamp() - philo->args->start_thread);
	printf(GREEN);
	printf("%llu all philos %s\n", stamp, str);
	printf(RESET);
	pthread_mutex_unlock(&philo->args->log);
}
