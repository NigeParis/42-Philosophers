/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/09/11 09:15:03 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *thread(void *arg)
{
    t_input_args *thread_data;
    thread_data = (t_input_args*)arg;
    pthread_mutex_lock(&thread_data->lock); 

    usleep(thread_data ->time_to_sleep * 1000);
    printf("inside thread_id %d\n", thread_data->philo[0].id);
    printf("inside thread_id %d\n", thread_data->philo[1].id);
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


    args.philo = ft_calloc(sizeof(pthread_t) , 2);

    if (is_number_of_args(argc))
        return (EXIT_FAILURE);

    
    ft_init_args(&args);
    if (parse_args(&args, argc,  argv))
        return (EXIT_FAILURE);
        
    pthread_mutex_init(&args.lock, NULL);
    
    gettimeofday(&current_time, NULL);
    args.start_time_sec = current_time.tv_sec;
    args.start_time_usec = current_time.tv_usec;

    
    pthread_create(&args.philo[0].thread, NULL, thread, &args);
    pthread_create(&args.philo[1].thread, NULL, thread, &args);
    args.philo[0].id = 1;
    args.philo[1].id = 2;
    dprintf(STDERR_FILENO, "here\n");

    long time;

    print_input(args, current_time);     // todo debug delete 

    while(1)
    {
        if(args.status > 0)
            break;
    }

    args.status = 1;
    pthread_join(args.philo[0].thread, NULL);
    pthread_join(args.philo[1].thread, NULL);
    printf("after thread\n");
    
    gettimeofday(&current_time, NULL);
    time = (((current_time.tv_sec * 1000) - (args.start_time_sec * 1000)) + ((current_time.tv_usec - args.start_time_usec) / 1000));
    
    
    
    
    printf("time : sec: '%lu'\n", time);

    return (EXIT_SUCCESS);
}