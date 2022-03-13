/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassamer <eassamer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:04:44 by eassamer          #+#    #+#             */
/*   Updated: 2022/03/13 12:00:59 by eassamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_struct(t_args *main_s)
{
	main_s->philo = malloc(sizeof(t_info) * main_s->num_philos);
	if (!main_s->philo)
	{
		free(main_s->philo);
		return (0);
	}
	main_s->forks = malloc(sizeof(t_info) * main_s->num_philos);
	if (!main_s->forks)
	{
		free(main_s->philo);
		return (0);
	}
	main_s->check_mutex = malloc(sizeof(pthread_mutex_t) * 1);
	if (!main_s->check_mutex)
	{
		free(main_s->check_mutex);
		return (0);
	}
	return (1);
}

int	check_digit(char *av)
{
	int	i;

	i = -1;
	while (++i)
	{
		if (!ft_isdigit(av[i]))
			return (0);
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (check_digit(av[i]) && ft_atoi(av[i]) <= 0)
			return (0);
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (((9 <= str[i] && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			break ;
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}
