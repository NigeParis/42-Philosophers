/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/27 09:00:08 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *table)
{
	t_input_args	*args;

	args = (t_input_args *)table;
	while ((all_full(args) != 2) && (end_all(args)) != 1)
	{
		philo_all_full(args->philo);
		if (args->stop == 2)
			put_are_full_log(args->philo, "are full");
		philo_is_dead(args);
		if (args->nbr_philo > 99)
			usleep(500);
	}
	return (NULL);
}

void	one_philo(t_input_args *args)
{
	long long int	stamp;
	int				id;

	stamp = 0;
	id = 1;
	pthread_mutex_lock(&args->log);
	pthread_mutex_lock(&args->death);
	stamp = (get_timestamp() - args->start_time);
	printf("%llu %d %s\n", stamp, id, "has taken a fork");
	ft_sleep(args->time_to_die, args);
	stamp = (get_timestamp() - args->start_time);
	printf("%llu %d %s\n", stamp, id, "died");
	pthread_mutex_unlock(&args->death);
	pthread_mutex_unlock(&args->log);
}

int	main(int argc, char *argv[])
{
	t_input_args	args;

	if (is_number_of_args(argc))
		return (EXIT_FAILURE);
	ft_init_args(&args);
	args.start_time = get_timestamp();
	if (parse_args(&args, argc, argv))
		return (EXIT_FAILURE);
	if (args.nbr_philo == 1)
	{
		if (init_mutex(&args))
			return (EXIT_FAILURE);
		return (one_philo(&args), EXIT_SUCCESS);
	}
	if (init_mutex(&args))
		return (EXIT_FAILURE);
	if (make_threads(&args))
		return (EXIT_FAILURE);
	if (destroy_mutex(&args))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
