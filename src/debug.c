/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:36:53 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/11 09:47:00 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_input(t_input_args args, struct timeval current_time)
{
	(void)current_time;
    

    printf("args forks = %d \n", args.nbr_forks);
    printf("args philo = %d \n", args.nbr_philo);
    printf("args die = %d \n", args.time_to_die);
    printf("args eat = %d \n", args.time_to_eat);
    printf("args sleep = %d \n", args.time_to_sleep);
    printf("args repas = %d \n", args.nbr_repas);

}