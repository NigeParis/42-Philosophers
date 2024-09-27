/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 08:42:34 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/27 18:48:43 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_threads(t_input_args *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philo)
	{
		if (pthread_create(&args->philo[i].thread, \
		NULL, &thread, &args->philo[i]))
			return (EXIT_FAILURE);
		pthread_mutex_lock(&args->lock);
		args->sync_nb_threads++;
		pthread_mutex_unlock(&args->lock);
		i++;
	}
	monitor(args);
	i = 0;
	while (i < args->nbr_philo)
	{
		if (pthread_join(args->philo[i].thread, NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	*thread(void *thread_philo)
{
	t_current_philo	*philo;
	t_input_args	*args;

	if (!thread_philo)
		return (NULL);
	philo = (t_current_philo *)thread_philo;
	args = philo->args;
	if (((philo->id) % 2 == 0) || philo->id == 5)
		ft_sleep(2);
	while (!end_all(args))
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (EXIT_SUCCESS);
}
