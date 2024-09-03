/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:32:33 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/03 10:37:55 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');   
}

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int is_negative_number(char *argv[])
{
    int i;

    i = 1;
    while (argv && argv[i])
    {
        if (is_not_number(argv[i]))
            return (error_args("Error - numbers only\n"), EXIT_FAILURE);
        if (ft_atoi(argv[i]) < 0)
		{
            error_args("Error - args less than zero or greater than INT_MAX\n");
            return (EXIT_FAILURE);
		}
		i++;
    }
    return (EXIT_SUCCESS);    
}

void	ft_putstr_fd(char *str, int fd)
{
	int		i;
	char	c;

	i = 0;
	if (!str)
		return ;
	while (str && str[i])
	{
		c = str[i];
		write(fd, &c, 1);
		i++;
	}
}
