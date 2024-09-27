/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads_actions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:18:55 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/27 08:48:53 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_current_philo *philo, int *left_fork, int *right_fork)
{
	if (*left_fork % 2 == 0)
	{
		pthread_mutex_lock(&philo->args->fork[*left_fork]);
		put_log(philo, "has taken a left  fork");
		usleep(60);
		pthread_mutex_lock(&philo->args->fork[*right_fork]);
		put_log(philo, "has taken a right fork");
	}
	else
	{
		pthread_mutex_lock(&philo->args->fork[*right_fork]);
		put_log(philo, "has taken a right fork");
		usleep(55);
		pthread_mutex_lock(&philo->args->fork[*left_fork]);
		put_log(philo, "has taken a left  fork");
	}	
}

void	drop_forks(t_current_philo *philo, int *left_fork, int *right_fork)
{
	pthread_mutex_unlock(&philo->args->fork[*left_fork]);
	usleep(60);
	pthread_mutex_unlock(&philo->args->fork[*right_fork]);
}

int	philo_eating(t_current_philo *philo)
{
	int	left_fork;
	int	right_fork;

	if (philo->is_full)
		usleep(500);
	pthread_mutex_lock(&philo->args->log);
	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->args->nbr_forks;
	pthread_mutex_unlock(&philo->args->log);
	get_forks(philo, &left_fork, &right_fork);
	put_log(philo, "is eating");
	pthread_mutex_lock(&philo->args->meal);
	philo->nbr_meals++;
	philo->last_meal = get_timestamp();
	if ((philo->args->nbr_repas > 0) && \
	(philo->nbr_meals >= philo->args->nbr_repas))
		philo->is_full = 1;
	pthread_mutex_unlock(&philo->args->meal);
	ft_sleep((long long)philo->args->time_to_eat, philo->args);
	drop_forks(philo, &left_fork, &right_fork);
	return (EXIT_SUCCESS);
}

int	philo_sleeping(t_current_philo *philo)
{
	put_log(philo, "is sleeping");
	ft_sleep((long long)philo->args->time_to_sleep, philo->args);
	return (EXIT_SUCCESS);
}

int	philo_thinking(t_current_philo *philo)
{
	put_log(philo, "is thinking");
	return (EXIT_SUCCESS);
}
