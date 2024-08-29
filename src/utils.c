/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:15:32 by nrobinso          #+#    #+#             */
/*   Updated: 2024/08/29 16:22:06 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');   
}

static int ft_isspace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

static int check_sign(char *str, int *i, int *neg_flag)
{
    while ((str && str[*i] == '-' ) || (str && str[*i] == '+'))
    {
        while (str && str[*i] == '-')
        {
            *neg_flag = -1;
            *i += 1;
        }
        while (str && str[*i] == '+')
        {
            *neg_flag = 1;
            *i += 1;
        }
    }
    return (*i);
}

int    ft_atoi(char *str)
{
    int  neg_flag;
    long nbr;
    int i;
    
    nbr = 0;
    i = 0;
    neg_flag = 1;
    if (!str)
        return (0);
    while (str && ft_isspace(str[i]))
        i++;    
    i = check_sign(str, &i, &neg_flag);
	if (!ft_isdigit(str[i]))
		return (-1);
    while (str && str[i] && ft_isdigit(str[i]))
    {
        nbr += str[i++] - '0';
        nbr *= 10;
		if ((!ft_isdigit(str[i])) && str[i] != '\0')
			return (-1);
    }
    nbr /=10;
	if (nbr > INT_MAX)
		return (-1);
    return ((int)(nbr * neg_flag));
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