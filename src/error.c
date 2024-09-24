/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nige42 <nige42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:17:05 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/24 21:21:01 by nige42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_args(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
}

int	is_number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		error_args("Error - number of arguments\n");
		error_args("./philo [philosophers] [die] [eat] \
		[sleep] ([meals] optional)\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
