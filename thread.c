/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassamer <eassamer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:15:18 by eassamer          #+#    #+#             */
/*   Updated: 2022/03/13 14:07:26 by eassamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(t_args *main_s)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < main_s->num_philos)
		{
			if (main_s->philo[i].time_ph_ate == main_s->num_time_eat)
				return (0);
			if (get_time() - main_s->philo->last_eat
				> (unsigned long) main_s->time_die)
			{
				usleep(1000);
				main_s->dead_philo = 1;
				pthread_mutex_lock(main_s->check_mutex);
				printf("\x1B[31m%lu | %d died\n",
					get_time() - main_s->start, main_s->philo[i].id);
				exit(0);
			}
			i++;
		}
	}
	return (1);
}

void	sleep_and_think(t_info *philo)
{
	if (philo->time_ph_ate != philo->main->num_time_eat)
	{
		pthread_mutex_lock(philo->main->check_mutex);
		printf("\x1B[35m%lu | %d is sleeping\n",
			get_time() - philo->main->start, philo->id);
		pthread_mutex_unlock(philo->main->check_mutex);
		wait_for_philo(philo->main->time_sleep);
		pthread_mutex_lock(philo->main->check_mutex);
		printf("\x1B[35m%lu | %d is thinking\n",
			get_time() - philo->main->start, philo->id);
		pthread_mutex_unlock(philo->main->check_mutex);
	}
}

void	routine(t_info *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->main->check_mutex);
	printf("\x1B[32m%lu | %d has taken the right fork\n",
		get_time() - philo->main->start, philo->id);
	pthread_mutex_unlock(philo->main->check_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->main->check_mutex);
	printf("\x1B[32m%lu | %d has taken the left fork\n",
		get_time() - philo->main->start, philo->id);
	pthread_mutex_unlock(philo->main->check_mutex);
	pthread_mutex_lock(philo->main->check_mutex);
	philo->last_eat = get_time();
	printf("\x1B[33m%lu | %d is eating\n",
		get_time() - philo->main->start, philo->id);
	pthread_mutex_unlock(philo->main->check_mutex);
	wait_for_philo(philo->main->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*life(void *a)
{
	t_info	*philo;

	philo = (t_info *)a;
	while (!philo->main->dead_philo
		&& philo->time_ph_ate != philo->main->num_time_eat)
	{
		routine(philo);
		sleep_and_think(philo);
		philo->time_ph_ate++;
	}
	return (NULL);
}

void	create_thread(t_args *main_s)
{
	int	i;

	main_s->start = get_time();
	i = 0;
	while (i < main_s->num_philos)
	{
		pthread_create(&main_s->philo[i].th, NULL,
			life, &main_s->philo[i]);
		usleep(100);
		i += 2;
	}
	i = 1;
	while (i < main_s->num_philos)
	{
		pthread_create(&main_s->philo[i].th,
			NULL, life, &main_s->philo[i]);
		usleep(100);
		i += 2;
	}
	if (!check(main_s))
		return ;
	i = -1;
	while (++i < main_s->num_philos)
		pthread_join(main_s->philo[i].th, NULL);
}
