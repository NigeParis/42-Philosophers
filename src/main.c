/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/17 18:37:46 by nrobinso         ###   ########.fr       */
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
        philo->args->stop = 1;
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
        if (philo->nbr_meals >= philo->args->nbr_repas)
        {
            philo->is_full = 1;
        }
        philo_sleeping(philo);
        put_log(philo, "is thinking");
        if (philo_is_dead(philo))
            break ;
        if (!((philo->nbr_meals < philo->args->nbr_repas) || (philo->args->nbr_repas < 1)))
            break ;
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
       
    pthread_mutex_init(&args.log, NULL);
    pthread_mutex_init(&args.lock, NULL);
    pthread_mutex_init(&args.death, NULL);

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
        //usleep(1);
  

        if (args.stop || args.philo->is_full)
           break; 
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
