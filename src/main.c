/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/13 17:11:32 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"


void    philo_sleeping(t_current_philo *philo)
{
    put_log(philo, "is sleeping");
    usleep(philo->args->time_to_sleep * 1000);    
}

void    philo_eating(t_current_philo *philo)
{
    pthread_mutex_lock(&philo->args->lock); 
    if (philo->nbr_meals < philo->args->nbr_repas)
        philo->args->status = 1;
    put_log(philo, "is eating");
    philo->nbr_meals++;
    usleep(philo->args->time_to_eat * 1000);    
    pthread_mutex_unlock(&philo->args->lock); 

}

void *thread(void *thread_philo)
{
    struct timeval current_time;
    t_current_philo *philo;
    t_input_args *args;

    philo = (t_current_philo *)thread_philo;
    args = philo->args;

    philo->start_time = get_timestamp(&current_time);
   
    while (philo->nbr_meals < philo->args->nbr_repas)
    {
        philo_eating(philo);
        philo_sleeping(philo);
        put_log(philo, "is thinking");
        
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
       
    pthread_mutex_init(&args.lock, NULL);

    i = 0;
    while (i < args.nbr_philo)
    {
        args.philo[i].id = i + 1;
        args.philo[i].args = &args;
        pthread_create(&args.philo[i].thread, NULL, &thread, &args.philo[i]);
        i++;
    }


    i = 0;

    while (i < args.nbr_philo)
    {
        pthread_join(args.philo[i].thread, NULL);
        i++;
    }

    i = 0;







    printf("end threads\n");
    printf("total_time : usec: '%lu'\n", total_time(&args, &current_time));
    return (EXIT_SUCCESS);
}
