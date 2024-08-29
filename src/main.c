/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/08/29 16:29:49 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void thread_1(void *arg)
{
    (void)arg;

    printf("inside thread_1\n");
    pthread_exit(EXIT_SUCCESS);
    
}




int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    input_args args;

    if (argc < 5 || argc > 6)
        return (error_args("Error - number of arguments\n"), EXIT_FAILURE);
    ft_init_args(&args);
    if (parse_args(&args, argc,  argv))
        return (error_args("Error - arguments format\n"), EXIT_FAILURE);
    

   
    printf("args forks = %d \n", args.nbr_forks);
    printf("args philo = %d \n", args.nbr_philo);
    printf("args die = %d \n", args.time_to_die);
    printf("args eat = %d \n", args.time_to_eat);
    printf("args sleep = %d \n", args.time_to_sleep);
    printf("args repas = %d \n", args.nbr_repas);



    // pthread_t thread1;

    // pthread_create(&thread1, NULL, (void *)thread_1, NULL);
    // pthread_detach(thread1);
    // printf("after thread\n");

    return (EXIT_SUCCESS);
}