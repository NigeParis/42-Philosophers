/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/18 09:10:01 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"


int philo_is_dead(t_current_philo *philo)
{
    struct timeval current_time;
    
    pthread_mutex_lock(&philo->args->lock); 
    pthread_mutex_lock(&philo->args->death); 
    if (((get_timestamp(&current_time) - philo->last_meal) > philo->args->time_to_die))
    {
        // dprintf(STDERR_FILENO, "DIED at :'%ld'\n", (long int)((get_timestamp(&current_time) - philo->last_meal) + philo->args->time_to_sleep) - philo->args->time_to_die);
        put_death_log(philo, "died");
        pthread_mutex_lock(&philo->args->meal); 
        philo->args->stop = 1;
        pthread_mutex_unlock(&philo->args->meal); 

        pthread_mutex_unlock(&philo->args->death); 
        pthread_mutex_unlock(&philo->args->lock); 
        return (1);
    }
    pthread_mutex_unlock(&philo->args->death); 
    pthread_mutex_unlock(&philo->args->lock); 
    return (0);
}


void    philo_sleeping(t_current_philo *philo)
{
    put_log(philo, "is sleeping");
    usleep(philo->args->time_to_sleep * 1000);    
}






int    philo_eating(t_current_philo *philo, struct timeval *current_time)
{
        
    
    
    pthread_mutex_lock(&philo->args->lock); 
    
    put_log(philo, "is eating");
    philo->last_meal = get_timestamp(current_time);
    philo->nbr_meals++;
    usleep(philo->args->time_to_eat * 998);
    
    if (philo->nbr_meals >= philo->args->nbr_repas)
    {
        pthread_mutex_lock(&philo->args->meal); 
        philo->is_full = 1;
        pthread_mutex_unlock(&philo->args->meal); 
    }

    pthread_mutex_unlock(&philo->args->lock); 
  

    
    return (0);
}

void *thread(void *thread_philo)
{
    struct timeval current_time;
    t_current_philo *philo;
    t_input_args *args;

    philo = (t_current_philo *)thread_philo;
    philo->start_time = get_timestamp(&current_time);
    args = philo->args;

   
    while (1)
    {
        philo_eating(philo, &current_time);
     
        philo_sleeping(philo);
        put_log(philo, "is thinking");
        if (philo_is_dead(philo))
            break ;
            
        pthread_mutex_lock(&philo->args->meal); 
        if (!((philo->nbr_meals < philo->args->nbr_repas) || (philo->args->nbr_repas < 1)))
        {
            pthread_mutex_unlock(&philo->args->meal); 
            break ;
        }
        pthread_mutex_unlock(&philo->args->meal); 
        
    }

    return (0);    
}

int init_mutex(t_input_args *args)
{
    int i;

    i = 0;

    while (i < args->nbr_philo)
    {
       pthread_mutex_init(&args->fork[i], NULL);
        i++;
    }
    pthread_mutex_init(&args->log, NULL);
    pthread_mutex_init(&args->lock, NULL);
    pthread_mutex_init(&args->death, NULL);
    pthread_mutex_init(&args->meal, NULL);
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

    i = 0;
    while (i < args.nbr_philo)
    {
        args.philo[i].id = i + 1;
        args.philo[i].args = &args;
        pthread_create(&args.philo[i].thread, NULL, &thread, &args.philo[i]);
        i++;
    }

    while (1)
    {
        usleep(1);
  
        pthread_mutex_lock(&args.meal); 

        if (args.stop || args.philo->is_full)
        {
            pthread_mutex_unlock(&args.meal); 
            break; 
        }
        pthread_mutex_unlock(&args.meal); 
        
    }    



    i = 0;
    while (i < args.nbr_philo)
    {
        pthread_join(args.philo[i].thread, NULL);
        i++;
    }

    i = 0;






    if (!args.stop)
    {
        printf("end threads\n");
        printf("total_time : usec: '%lu'\n", total_time(&args));
    }
    return (EXIT_SUCCESS);
}
