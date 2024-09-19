/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/19 17:23:52 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

int end_all(t_input_args *args)
{
    int signal;

    signal = 0;
    pthread_mutex_lock(&args->death); 
    signal = args->stop;
    pthread_mutex_unlock(&args->death); 
    return (signal);
}

int set_end_all(t_input_args *args)
{
    pthread_mutex_lock(&args->death); 
    args->stop = 1;
    pthread_mutex_unlock(&args->death); 
    return (EXIT_SUCCESS);
}

long int    eat_time_left(t_input_args *args, int i)
{
    long int    result;

    result = 0;
    if (i < 0 || !args)
        return (0);
    result = (((args->philo[i].last_meal + args->time_to_die)\
    - args->philo[i].last_meal) - args->time_to_eat);
    return (result);
} 



int philo_is_dead(t_input_args *args)
{
    struct timeval current_time;
    int i;

    i = 0;
    if (!args)
        return (printf("error pas args\n") ,EXIT_FAILURE);
    if (end_all(args))
        return (1);
    pthread_mutex_lock(&args->lock); 
    pthread_mutex_lock(&args->meal); 
    while (i < args->nbr_philo)
    {
        if (get_timestamp(&current_time) >= (args->philo[i].last_meal + args->time_to_die))
        {
            dprintf(STDERR_FILENO, "\n           last__meal[%d] '%lu'\n",args->philo->id - 1, args->philo[i].last_meal);
            dprintf(STDERR_FILENO, "   time awaiting meal[%d] '%lu' ms:'%ld'\n",args->philo->id - 1, (args->philo[i].last_meal + args->time_to_die),eat_time_left(args, i));
            
            
            dprintf(STDERR_FILENO, "           time stamp[%d] '%lu'\n",args->philo->id - 1, get_timestamp(&current_time));
            
            dprintf(STDERR_FILENO, "      total_time_left_to_live[%d] '%ld'\n",args->philo->id - 1, (eat_time_left(args, i) - args->time_to_sleep));



            
            dprintf(STDERR_FILENO, "          time to die[%d] '%d'\n\n",args->philo->id - 1, args->time_to_die);
            put_death_log(&args->philo[i], "died");
            set_end_all(args);
            pthread_mutex_unlock(&args->meal); 
            pthread_mutex_unlock(&args->lock); 
            return (1);
        }

        i++;

    }
    
    pthread_mutex_unlock(&args->meal); 
    pthread_mutex_unlock(&args->lock); 
    return (0);
}


int    philo_sleeping(t_current_philo *philo)
{
    if (end_all(philo->args))
        return (1);
    put_log(philo, "is sleeping");
    usleep(philo->args->time_to_sleep * 1000);    
    return (0);
}


int check_death(t_input_args *args)
{
    int i;
    
    i = 0;
    if (!args)
        return (EXIT_FAILURE);
        
    if (philo_is_dead(args))
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}



int    philo_eating(t_current_philo *philo)
{

    struct timeval current_time;
    
    if (end_all(philo->args))
        return (1);
    pthread_mutex_lock(&philo->args->lock); 
    pthread_mutex_lock(&philo->args->meal); 
    
    put_log(philo, "is eating");
    philo->nbr_meals++;
    philo[philo->id - 1].last_meal = get_timestamp(&current_time);
    dprintf(STDERR_FILENO, "       recorded last_meal[%d] '%lu'\n",philo->id - 1, philo[philo->id - 1].last_meal);
    
    usleep(philo->args->time_to_eat * 998);
    
    if (philo->nbr_meals >= philo->args->nbr_repas)
    {
        philo->is_full = 1;
    }
    pthread_mutex_unlock(&philo->args->meal); 
    pthread_mutex_unlock(&philo->args->lock); 
  

    
    return (0);
}

void    *monitor(void *table)
{
    t_input_args *args;
    
    args = (t_input_args*)table;    
    while (!end_all(args))
    {
        if (check_death(args))
        {
            break ;
        }
        usleep(1);
    }
    return (NULL);    
}



void *thread(void *thread_philo)
{
    struct timeval current_time;
    t_current_philo *philo;
    t_input_args *args;

    philo = (t_current_philo *)thread_philo;
    philo->start_time = get_timestamp(&current_time);
    args = philo->args;

   
    while (!end_all(args))
    {
        philo_eating(philo);            
        philo_sleeping(philo);
        put_log(philo, "is thinking");
            
        // pthread_mutex_lock(&philo->args->meal); 
        // if (!((philo->nbr_meals < philo->args->nbr_repas) || (philo->args->nbr_repas < 1)))
        // {
        //     pthread_mutex_unlock(&philo->args->meal); 
        //     break ;
        // }
        // pthread_mutex_unlock(&philo->args->meal); 
        
    }

    return (0);    
}



int main(int argc, char *argv[])
{
    int i;
    t_input_args args;
    struct timeval current_time;

    i = 0;

    if (is_number_of_args(argc))
        return (EXIT_FAILURE);
    
    ft_init_args(&args);
    if (parse_args(&args, argc, argv))
        return (EXIT_FAILURE);

       
   
    args.start_thread = get_timestamp(&current_time);
    init_mutex(&args);

    if (make_threads(&args))
        return (EXIT_FAILURE);





    if (!args.stop)
    {
        printf("end threads\n");
        printf("total_time : usec: '%lu'\n", total_time(&args));
    }
    return (EXIT_SUCCESS);
}
