/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/11 18:28:29 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

void *thread(void *p)
{
    struct timeval current_time;
    t_current_philo *philo;
    t_input_args *args;

    philo = (t_current_philo *)p;
    args = philo->args;
    
    pthread_mutex_lock(&args->lock); 

    gettimeofday(&current_time, NULL);
    philo->start_time = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
    usleep(args->time_to_sleep * 1000);
    
    args->status = 1;
    printf( "%lu ms philo[%d]\n", ((philo->start_time - args->start_thread) + args->time_to_sleep), philo->id);
  
  
  
    pthread_mutex_unlock(&args->lock);
    pthread_exit(EXIT_SUCCESS);    
}







int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    int i;
    t_input_args args;
    struct timeval current_time;

    i = 0;

    if (is_number_of_args(argc))
        return (EXIT_FAILURE);
    
    ft_init_args(&args);
    if (parse_args(&args, argc, argv))
        return (EXIT_FAILURE);

    gettimeofday(&current_time, NULL);
    args.start_thread = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
       
    pthread_mutex_init(&args.lock, NULL);

    i = 0;
    while (i < args.nbr_philo)
    {
        args.philo[i].id = i + 1;
        args.philo[i].args = &args;
        pthread_create(&args.philo[i].thread, NULL, &thread, &args.philo[i]);
        i++;
    }

    while(1)
    {
        if(args.status == 1)
        {
            break;
        }            
    }

    args.status = 1;

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
