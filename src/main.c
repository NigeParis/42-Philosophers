/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/20 14:27:22 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

int end_all(t_input_args *args)
{
    int signal;

    signal = 0;
    pthread_mutex_lock(&args->check_death); 
    signal = args->stop;
    pthread_mutex_unlock(&args->check_death); 
    return (signal);
}

int set_end_all(t_input_args *args)
{
    pthread_mutex_lock(&args->death); 
    args->stop = 1;
    pthread_mutex_unlock(&args->death); 
    return (EXIT_SUCCESS);
}

long long int    eat_time_left(t_input_args *args, int i)
{
    long long int    result;

    result = 0;
    if (i < 0 || !args)
        return (0);
    result = (((args->philo[i].last_meal + args->time_to_die)\
    - args->philo[i].last_meal) - args->time_to_eat);
    return (result);
} 

long long int    life_time_left(t_input_args *args, int i)
{
    long long int    result;

    result = 0;
    if (i < 0 || !args)
        return (0);
    result = (eat_time_left(args, i) - args->time_to_sleep);
    return (result);
} 


int philo_is_dead(t_input_args *args)
{
    int i;

    i = 0;
    if (!args)
        return (printf("error pas args\n") ,EXIT_FAILURE);
    if (end_all(args))
        return (1);
    while (i < args->nbr_philo)
    {
        pthread_mutex_lock(&args->meal);
        if (eat_time_left(args, i) < 0)
        {
            put_log(&args->philo[i], "died");
            set_end_all(args);
            
 


            pthread_mutex_unlock(&args->meal); 
            return (1);
        }
        pthread_mutex_unlock(&args->meal); 
        i++;

    }
    return (0);
}

void    ft_sleep(long long wait, t_input_args *args)
{
    long long time;
    time = get_timestamp() + wait;
    while (!end_all(args) && get_timestamp() < time)
        usleep(50); 

 
    
}


int    philo_sleeping(t_current_philo *philo)
{
    put_log(philo, "is sleeping");
    ft_sleep(philo->args->time_to_sleep, philo->args);
    //usleep(philo->args->time_to_sleep * 1000); 
    return (0);
}


int check_death(t_input_args *args)
{
    if (!args)
        return (EXIT_FAILURE);
        
    if (philo_is_dead(args))
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

int philo_thinking(t_current_philo *philo)
{
    put_log(philo, "is thinking");
    
    return (EXIT_SUCCESS);
}





int    philo_eating(t_current_philo *philo)
{
    if (!philo)
        return (set_end_all(philo->args), EXIT_FAILURE);
    put_log(philo, "is eating");
    pthread_mutex_lock(&philo->args->meal); 
    philo->nbr_meals++;
    philo->last_meal = get_timestamp();
    
    //usleep(philo->args->time_to_eat * 1000);
    ft_sleep(philo->args->time_to_eat, philo->args);
    pthread_mutex_unlock(&philo->args->meal);  
    
    return (0);
}




void    *monitor(void *table)
{
    t_input_args *args;
    
    args = (t_input_args*)table;    
    while (!end_all(args))
    {
        // if (check_death(args))
        // {
        //     break ;
        // }
        usleep(500);
    }
    return (NULL);    
}

void *thread(void *thread_philo)
{
    t_current_philo *philo;
    t_input_args *args;

    philo = (t_current_philo *)thread_philo;
    args = philo->args;
    
    start_philo_timer(args->start_thread); 

    while (!end_all(args))
    {
        philo_eating(philo);
        philo_sleeping(philo);
        philo_thinking(philo);
    }

    return (0);    
}



int main(int argc, char *argv[])
{
    t_input_args args;

    if (is_number_of_args(argc))
        return (EXIT_FAILURE);
    
    ft_init_args(&args);
    if (parse_args(&args, argc, argv))
        return (EXIT_FAILURE);

    args.start_thread = get_timestamp() + (30 * args.nbr_philo);   
   
    if (init_mutex(&args))
        return (EXIT_FAILURE);


    if (make_threads(&args))
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}
