/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:19:39 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/03 12:58:35 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define MAX_PHILO 200
# define MIN_TIME 60

typedef struct input_params
{
	int 	nbr_philo;
	int		nbr_forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_repas;
	int		status;
	long	start_time_sec;
	long	start_time_usec;
	
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
int		is_number_of_args(int argc);
int		is_negative_number(char *argv[]);
int 	is_too_many_philo(int philo);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		is_not_enough_time(int time);
int		is_not_number(char *arg);
int	is_no_meal(int meal);


/// @brief function collects args and parses in to structure args
/// @param args 
/// @param argc 
/// @param argv 
/// @return SUCCESS or FAILURE
int		parse_args(input_args *args, int argc, char *argv[]);


#endif