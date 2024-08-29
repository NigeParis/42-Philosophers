/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:19:39 by nrobinso          #+#    #+#             */
/*   Updated: 2024/08/29 16:26:52 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>

typedef struct input_params
{
	int 	nbr_philo;
	int		nbr_forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_repas;
	
} input_args;


/// @brief function ft_atoi modified
/// @brief acceptes ----1 +++5  "    -89"
/// @param str 
/// @return -1 if bigger than INT_MAX
int		ft_atoi(char *str);
/// @brief initalise to zero all int in the stucture
/// @brief checks if args exists
/// @param args 
void	ft_init_args(input_args *args);
void	ft_putstr_fd(char *str, int fd);
void	error_args(char *str);
/// @brief function collects args and parses in to structure args
/// @param args 
/// @param argc 
/// @param argv 
/// @return SUCCESS or FAILURE
int parse_args(input_args *args, int argc, char *argv[]);


#endif