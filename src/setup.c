/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:37:27 by nrobinso          #+#    #+#             */
/*   Updated: 2024/08/29 16:27:29 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_init_args(input_args *args)
{
	if (!args)
		return ;
    args->nbr_philo = 0;
    args->nbr_forks = 0;
    args->time_to_die = 0;
    args->time_to_eat = 0;
    args->time_to_sleep = 0;
    args->nbr_repas = 0;    
}

int parse_args(input_args *args, int argc, char *argv[])
{
    int i;

    i = 1;
    while (argv && argv[i])
    {
        if (ft_atoi(argv[i]) < 0)
            return (EXIT_FAILURE);
        args->nbr_philo = ft_atoi(argv[1]);
        args->nbr_forks = ft_atoi(argv[1]);
        args->time_to_die = ft_atoi(argv[2]);
        args->time_to_eat = ft_atoi(argv[3]);
        args->time_to_sleep = ft_atoi(argv[4]);
        if (argc == 6)
            args->nbr_repas = ft_atoi(argv[5]);
        i++;
    }
    return (EXIT_SUCCESS); 
}

