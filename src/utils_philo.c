/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:32:33 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/19 15:28:15 by nrobinso         ###   ########.fr       */
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
        if (ft_atoi(argv[i]) < 1)
		{
            error_args("Error - args less than 1 or greater than INT_MAX\n");
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

void    *ft_calloc(size_t nb_elements , size_t size)
{
    void    *ptr;
    size_t  total_size;
    size_t  i;
    char    *c;

    i = 0;
    if (nb_elements == 0)
        return (malloc(0));
    if (nb_elements > SIZE_MAX / size)
        return (0);
    total_size = nb_elements * size;
    ptr = (void*)malloc(nb_elements * size);
    if (!ptr)
        return (0);
    c = (char*)ptr;
    while (i < total_size)
        c[i++] = 0;
    return (ptr);
}



void    put_log(t_current_philo *philo, char *str)
{
    struct timeval current_time;

    pthread_mutex_lock(&philo->args->log); 
    pthread_mutex_lock(&philo->args->death); 
    
    if ((!philo->args->stop) && (!philo->is_full))
        printf("%lu ms philo[%d] %s\n", \
    (get_timestamp(&current_time) - philo->args->start_thread), philo->id - 1, str);
    pthread_mutex_unlock(&philo->args->death); 
    pthread_mutex_unlock(&philo->args->log); 
    
}



void    put_death_log(t_current_philo *philo, char *str)
{
    struct timeval current_time;

    pthread_mutex_lock(&philo->args->log); 
    pthread_mutex_lock(&philo->args->death); 
    
    if (!philo->args->stop)
        printf("%lu ms philo[%d] %s\n", ((get_timestamp(&current_time) - philo->args->start_thread) + philo->args->time_to_sleep), philo->id - 1, str);
    pthread_mutex_unlock(&philo->args->death); 
    pthread_mutex_unlock(&philo->args->log); 
    
}


