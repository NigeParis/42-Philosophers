/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:17:17 by nrobinso          #+#    #+#             */
/*   Updated: 2024/08/23 12:52:57 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thread_1(void *arg)
{
    (void)arg;
    sleep(10);

    printf("inside thread_1\n");
    pthread_exit(EXIT_SUCCESS);
    
}


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    pthread_t thread1;

    pthread_create(&thread1, NULL, (void *)thread_1, NULL);
    pthread_detach(thread1);
    printf("after thread\n");
    sleep(2);
    printf("helloword\n");

    return (EXIT_SUCCESS);
}