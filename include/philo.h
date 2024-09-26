/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:19:39 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/26 13:09:36 by nrobinso         ###   ########.fr       */
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

struct						s_input_args;

typedef struct s_input_args	t_input_args;

typedef struct s_life_of_philo
{
	int				id;
	int				nbr_meals;
	int				is_full;
	long long		last_meal;
	pthread_t		thread;
	t_input_args	*args;
}	t_current_philo;

typedef struct s_input_args
{
	int				nbr_philo;
	int				nbr_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_repas;
	int				stop;
	int				sync_nb_threads;
	long long		start_time;
	long long		stop_thread;
	pthread_mutex_t	death;
	pthread_mutex_t	lock;
	pthread_mutex_t	log;
	pthread_mutex_t	meal;
	pthread_mutex_t	fork[MAX_PHILO];
	t_current_philo	philo[MAX_PHILO];

}	t_input_args;

int				ft_atoi(char *str);
void			ft_init_args(t_input_args *args);
void			ft_putstr_fd(char *str, int fd);
void			error_args(char *str);
int				is_number_of_args(int argc);
int				is_negative_number(char *argv[]);
int				is_too_many_philo(int philo);
int				ft_isdigit(char c);
int				ft_isspace(char c);
int				is_not_enough_time(int time);
int				is_not_number(char *arg);
int				parse_args(t_input_args *args, int argc, char *argv[]);
void			put_log(t_current_philo *philo, char *str);
void			put_death_log(t_current_philo *philo, char *str);
long long		get_timestamp(void);
int				init_mutex(t_input_args *args);
int				make_threads(t_input_args *args);
void			*monitor(void *args);
void			*thread(void *thread_philo);
int				end_all(t_input_args *args);
int				set_end_all(t_input_args *args);
int				philo_eating(t_current_philo *philo);
int				philo_sleeping(t_current_philo *philo);
int				philo_thinking(t_current_philo *philo);
void			ft_sleep(long long wait, t_input_args *args);
int				philo_is_dead(t_input_args *args);
void			put_are_full_log(t_current_philo *philo, char *str);
void			put_death_log(t_current_philo *philo, char *str);
int				philo_all_full(t_current_philo *philo);
int				all_full(t_input_args *args);
void			get_forks(t_current_philo *philo, int *fork_a, int *fork_b);
void			drop_forks(t_current_philo *philo, int *fork_a, int *fork_b);
void			debug_print_input(t_input_args *args, \
				t_current_philo *philo, int i);
int				destroy_mutex(t_input_args *args);



#endif
