/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:37:27 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/26 13:09:06 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_args(t_input_args *args)
{
	int			i;
	long long	time;

	i = 0;
	time = get_timestamp();
	if (!args)
		return ;
	args->nbr_forks = 0;
	args->nbr_philo = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->nbr_repas = 0;
	args->stop = 0;
	args->start_time = 0;
	args->sync_nb_threads = 0;
	while (i < MAX_PHILO)
	{
		args->philo[i].id = i;
		args->philo[i].args = args;
		args->philo[i].nbr_meals = 0;
		args->philo[i].is_full = 0;
		args->philo[i].last_meal = time;
		args->philo[i].thread = 0;
		i++;
	}
}

int	parse_args(t_input_args *args, int argc, char *argv[])
{
	if (is_negative_number(argv))
		return (EXIT_FAILURE);
	args->nbr_philo = ft_atoi(argv[1]);
	if (is_too_many_philo(args->nbr_philo))
		return (error_args("Error - nbr of philo,s > 200\n"), EXIT_FAILURE);
	args->nbr_forks = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	if (is_not_enough_time(args->time_to_die))
		return (error_args("Error - time to die < 60\n"), EXIT_FAILURE);
	args->time_to_eat = ft_atoi(argv[3]);
	if (is_not_enough_time(args->time_to_eat))
		return (error_args("Error - time to eat < 60\n"), EXIT_FAILURE);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (is_not_enough_time(args->time_to_sleep))
		return (error_args("Error - time to sleep < 60\n"), EXIT_FAILURE);
	if (argc == 6)
	{
		args->nbr_repas = ft_atoi(argv[5]);
		if (args->nbr_repas < 1)
			return (error_args("Error - number of meals less than 1\n"), \
			EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_mutex(t_input_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&args->log, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&args->lock, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&args->death, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&args->meal, NULL))
		return (EXIT_FAILURE);
	while (i < args->nbr_philo)
	{
		if (pthread_mutex_init(&args->fork[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}



int	destroy_mutex(t_input_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&args->log))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&args->lock))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&args->death))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&args->meal))
		return (EXIT_FAILURE);
	while (i < args->nbr_philo)
	{
		if (pthread_mutex_destroy(&args->fork[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
