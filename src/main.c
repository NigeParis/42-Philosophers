/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/24 22:25:14 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	eat_time_left(t_input_args *args, int i)
{
	long long int	result;

	result = 0;
	if (i < 0 || !args)
		return (0);
	result = (((args->philo[i].last_meal + args->time_to_die) \
	- args->philo[i].last_meal) - args->time_to_eat);
	return (result);
}

long long int	life_time_left(t_input_args *args, int i)
{
	long long int	result;

	result = 0;
	if (i < 0 || !args)
		return (0);
	result = (eat_time_left(args, i) - args->time_to_sleep);
	return (result);
}

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
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_input_args	args;

	if (is_number_of_args(argc))
		return (EXIT_FAILURE);
	ft_init_args(&args);
	if (parse_args(&args, argc, argv))
		return (EXIT_FAILURE);
	if (args.nbr_philo == 1)
		return (0);
	args.start_thread = get_timestamp();
	if (init_mutex(&args))
		return (EXIT_FAILURE);
	if (make_threads(&args))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
