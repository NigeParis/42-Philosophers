/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/03 15:16:49 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thread(void *arg)
{
    t_input_args *thread_data;
    thread_data = (t_input_args*)arg;
    pthread_mutex_lock(&thread_data->lock); 

    usleep(thread_data ->time_to_sleep * 1000);
    printf("inside thread_1 %d\n", thread_data->time_to_sleep);
    thread_data ->status = 1;
    pthread_mutex_unlock(&thread_data->lock); 
    pthread_exit(EXIT_SUCCESS);    
}




int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    t_input_args args;
    struct timeval current_time;

    if (is_number_of_args(argc))
        return (EXIT_FAILURE);

    
    ft_init_args(&args);
    if (parse_args(&args, argc,  argv))
        return (EXIT_FAILURE);
    gettimeofday(&current_time, NULL);
    args.start_time_sec = current_time.tv_sec;
    args.start_time_usec = current_time.tv_usec;
    pthread_mutex_init(&args.lock, NULL);


    
    printf("time : sec: '%lu' milli:'%lu'\n", args.start_time_sec, current_time.tv_usec);

    printf("args forks = %d \n", args.nbr_forks);
    printf("args philo = %d \n", args.nbr_philo);
    printf("args die = %d \n", args.time_to_die);
    printf("args eat = %d \n", args.time_to_eat);
    printf("args sleep = %d \n", args.time_to_sleep);
    printf("args repas = %d \n", args.nbr_repas);

    

    pthread_t thread1;
    long time;

    pthread_create(&thread1, NULL, (void *)thread, (void*)&args);

    while(1)
    {
        if(args.status > 0)
            break;
    }

    args.status = 1;
    pthread_join(thread1, NULL);
    printf("after thread\n");
    
    gettimeofday(&current_time, NULL);
    time = (((current_time.tv_sec * 1000) - (args.start_time_sec * 1000)) + ((current_time.tv_usec - args.start_time_usec) / 1000));
    
    
    
    
    printf("time : sec: '%lu'\n", time);

    return (EXIT_SUCCESS);
}