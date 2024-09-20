/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:19:39 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/20 13:06:12 by nrobinso         ###   ########.fr       */
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
# include <stdint.h>


# define MAX_PHILO 250
# define MIN_TIME 60

struct s_input_args; // Forward declaration

typedef struct s_input_args t_input_args;


typedef struct s_life_of_philo
{
	int			id;
	int			nbr_meals;
	int			is_full;
	long		start_time;
	long long   last_meal;

	pthread_t thread;


	t_input_args *args;
}	t_current_philo;

typedef struct s_input_args
{
	int		id;
	int 	nbr_philo;
	int		nbr_forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_repas;
	int		status;
	int		stop;
	long	start_thread;
	
	//pthread_t handler;

	pthread_mutex_t check_death;
	pthread_mutex_t death;
	pthread_mutex_t lock;
	pthread_mutex_t log;
	pthread_mutex_t meal;
	t_current_philo	philo[MAX_PHILO];
	//t_current_philo	*philo;
	
} t_input_args;




/// @brief function ft_atoi modified
/// @brief acceptes ----1 +++5  "    -89"
/// @param str 
/// @return -1 if bigger than INT_MAX
int		ft_atoi(char *str);

/// @brief initalise to zero all int in the stucture
/// @brief checks if args exists
/// @param args 
void	ft_init_args(t_input_args *args);

void	ft_putstr_fd(char *str, int fd);
void	error_args(char *str);
int		is_number_of_args(int argc);
int		is_negative_number(char *argv[]);
int 	is_too_many_philo(int philo);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		is_not_enough_time(int time);
int		is_not_number(char *arg);



/// @brief function collects args and parses in to structure args
/// @param args 
/// @param argc 
/// @param argv 
/// @return SUCCESS or FAILUREget_timestamp
int		parse_args(t_input_args *args, int argc, char *argv[]);

void	print_input(t_input_args *args, t_current_philo *philo, int i);

void    put_log(t_current_philo *philo, char *str);
void    put_death_log(t_current_philo *philo, char *str);
long	long	get_timestamp(void);


void    *ft_calloc(size_t nb_elements , size_t size);

int		init_mutex(t_input_args *args);
int		make_threads(t_input_args *args);
void    *monitor(void *args);
void	*thread(void *thread_philo);

int		end_all(t_input_args *args);
int		set_end_all(t_input_args *args);

void    start_philo_timer(long waitime);
long long int    eat_time_left(t_input_args *args, int i);
long long int    life_time_left(t_input_args *args, int i);


#endif