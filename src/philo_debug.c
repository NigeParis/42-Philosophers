/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:36:53 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/25 12:46:15 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	debug_print_input(t_input_args *args, t_current_philo *philo, int i)
{
	(void)philo;
	dprintf(STDERR_FILENO, "args forks = %d \n", args->nbr_forks);
	dprintf(STDERR_FILENO, "args philo = %d \n", args->nbr_philo);
	dprintf(STDERR_FILENO, "args die = %d \n", args->time_to_die);
	dprintf(STDERR_FILENO, "args eat = %d \n", args->time_to_eat);
	dprintf(STDERR_FILENO, "args sleep = %d \n", args->time_to_sleep);
	dprintf(STDERR_FILENO, "args repas = %d \n", args->nbr_repas);
	dprintf(STDERR_FILENO, "\n             last__meal[%d] '%llu'\n", \
	args->philo->id, args->philo[i].last_meal);
	dprintf(STDERR_FILENO, "             time stamp[%d] '%lld'\n", \
	args->philo->id, get_timestamp());
	dprintf(STDERR_FILENO, "            time to die[%d] '%d'\n", \
	args->philo->id, args->time_to_die);
}
