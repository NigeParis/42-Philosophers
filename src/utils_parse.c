/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:57:45 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/03 10:59:05 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_too_many_philo(int philo)
{
    if (philo > MAX_PHILO)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int is_not_enough_time(int time)
{
    if (time < MIN_TIME)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);   
}

int is_not_number(char *arg)
{
    int i;

    i = 0;
    while (arg && arg[i])
    {
		if ((arg[i] == '-') && i == 0)
			i++; 
        if (!ft_isdigit(arg[i]))
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}
