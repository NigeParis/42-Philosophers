/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:36:53 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/19 08:06:09 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_input(t_input_args args, struct timeval current_time)
{
	(void)current_time;
    

    dprintf(STDERR_FILENO,"args forks = %d \n", args.nbr_forks);
    dprintf(STDERR_FILENO,"args philo = %d \n", args.nbr_philo);
    dprintf(STDERR_FILENO,"args die = %d \n", args.time_to_die);
    dprintf(STDERR_FILENO,"args eat = %d \n", args.time_to_eat);
    dprintf(STDERR_FILENO,"args sleep = %d \n", args.time_to_sleep);
    dprintf(STDERR_FILENO,"args repas = %d \n", args.nbr_repas);

}