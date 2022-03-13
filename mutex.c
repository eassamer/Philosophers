/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassamer <eassamer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:43:08 by eassamer          #+#    #+#             */
/*   Updated: 2022/03/13 14:00:11 by eassamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_mutex(t_args *main_s)
{
	int	i;

	i = 0;
	pthread_mutex_init(main_s->check_mutex, NULL);
	while (i < main_s->num_philos)
	{
		if (pthread_mutex_init(&main_s->forks[i], NULL) != 0)
		{
			write(2,"failed to init mutexs\n",22);
			destroy_all(main_s);
			break ;
		}
		main_s->philo[i].id = i + 1;
		main_s->philo[i].right_fork = &main_s->forks[i];
		if (i == 0)
			main_s->philo[i].left_fork = &main_s->forks[main_s->num_philos - 1];
		else
			main_s->philo[i].left_fork = &main_s->forks[i - 1];
		i++;
	}
}

void	destroy_all(t_args *main_s)
{
	int	i;

	i = 0;
	free(main_s->philo);
	free(main_s->forks);
	while (i < main_s->num_philos)
	{
		pthread_mutex_destroy(&main_s->forks[i]);
		i++;
	}
	pthread_mutex_destroy(main_s->check_mutex);
}
