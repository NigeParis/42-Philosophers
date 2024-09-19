/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/19 19:56:04 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

int end_all(t_input_args *args)
{
    int signal;

    signal = 0;
    pthread_mutex_lock(&args->lock); 
    signal = args->stop;
    pthread_mutex_unlock(&args->lock); 
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

long int    life_time_left(t_input_args *args, int i)
{
    long int    result;

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
        if (life_time_left(args, i) < 0)
        {
            set_end_all(args);
            put_log(&args->philo[i], "died");
            
            dprintf(STDERR_FILENO, "\n             last__meal[%d] '%lu'\n",args->philo->id - 1, args->philo[i].last_meal);
            dprintf(STDERR_FILENO, "     time awaiting meal[%d] '%lu' ms:'%ld'\n",args->philo->id - 1, (args->philo[i].last_meal + args->time_to_die),eat_time_left(args, i));
            //dprintf(STDERR_FILENO, "             time stamp[%d] '%lu'\n",args->philo->id - 1, get_timestamp(&current_time));
            dprintf(STDERR_FILENO, "total_time_left_to_live[%d] '%ld'\n",args->philo->id - 1, life_time_left(args, i));            
            dprintf(STDERR_FILENO, "            time to die[%d] '%d'\n",args->philo->id - 1, args->time_to_die);
            dprintf(STDERR_FILENO, "       time stamp death[%d] '%ld'\n\n",args->philo->id - 1, \
            (get_timestamp() - life_time_left(args, i)));


            pthread_mutex_unlock(&args->meal); 
            return (1);
        }
        pthread_mutex_unlock(&args->meal); 
        i++;

    }
    return (0);
}


int    philo_sleeping(t_current_philo *philo)
{
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
    

    
    put_log(philo, "is eating");
    pthread_mutex_lock(&philo->args->meal); 
    philo->nbr_meals++;
    philo[philo->id - 1].last_meal = get_timestamp();
    //dprintf(STDERR_FILENO, "       recorded last_meal[%d] '%lu'\n",philo->id - 1, philo[philo->id - 1].last_meal);
    pthread_mutex_unlock(&philo->args->meal);  
  
    usleep(philo->args->time_to_eat * 1000);
    
    if (philo->nbr_meals >= philo->args->nbr_repas)
    {
        philo->is_full = 1;
    }

    
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
    }
    return (NULL);    
}



void *thread(void *thread_philo)
{
    // struct timeval current_time;
    t_current_philo *philo;
    t_input_args *args;

    philo = (t_current_philo *)thread_philo;
    // philo->start_time = get_timestamp(&current_time);
    args = philo->args;

   
    while (!end_all(args))
    {
        if (philo_eating(philo))
            break ;            
        if (philo_sleeping(philo))
            break ;
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

    i = 0;

    if (is_number_of_args(argc))
        return (EXIT_FAILURE);
    
    ft_init_args(&args);
    if (parse_args(&args, argc, argv))
        return (EXIT_FAILURE);

       
   
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
