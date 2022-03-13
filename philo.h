/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassamer <eassamer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:08:17 by eassamer          #+#    #+#             */
/*   Updated: 2022/03/13 14:05:25 by eassamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct philo
{
	int				id;
	pthread_t		th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	last_eat;
	int				time_ph_ate;
	int				dead;
	struct args		*main;
}	t_info;

typedef struct args
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_time_eat;
	int				dead_philo;
	long			time;
	unsigned long	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*check_mutex;
	t_info			*philo;
}	t_args;

// checker

int				check_digit(char *av);
int				check_args(int ac, char **av);
int				ft_isdigit(int c);
int				ft_atoi(char *str);
// parsing

void			parsing(int ac, char **av, t_args *main_s);
void			init_struct(t_args *main_s);
int				allocate_struct(t_args *main_s);

// mutex

void			create_mutex(t_args *main_s);
void			destroy_all(t_args *main_s);

// threads

void			create_thread(t_args *main_s);
void			*life(void *a);
int				check(t_args *main_s);
void			sleep_and_think(t_info *philo);
void			routine(t_info *philo);

//time

void			wait_for_philo(int time_to_wait);
unsigned long	get_time(void);
#endif
