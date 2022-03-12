#include "philo.h"

void create_mutex(t_args *main_s)
{
    int i;

    i = 0;
    pthread_mutex_init(main_s->check_mutex,NULL);
    while(i < main_s->num_philos)
    {
        if (i == 0)
        {
            pthread_mutex_init(&main_s->forks[i], NULL);
            main_s->philo[i].id = i + 1;
            main_s->philo[i].right_fork = &main_s->forks[i];
            main_s->philo[i].left_fork = &main_s->forks[main_s->num_philos - 1];
        }
        else
        {
            main_s->philo[i].id = i + 1;
            pthread_mutex_init(&main_s->forks[i], NULL);
            main_s->philo[i].right_fork = &main_s->forks[i];
            main_s->philo[i].left_fork = &main_s->forks[i - 1];
        }
        i++;
    }
}

void    destroy_mutex(t_args main_s)
{
    int i;

    i = 0;
    while (i < main_s.num_philos)
    {
        pthread_mutex_destroy(&main_s.forks[i]);
        i++;
    }
    pthread_mutex_destroy(main_s.check_mutex);
}