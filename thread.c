# include "philo.h"

int check(t_args *main_s)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < main_s->num_philos)
        {
            if (main_s->philo[i].time_ph_ate == main_s->num_time_eat)
                return (0);
            if (get_time() - main_s->philo->last_eat > main_s->time_eat)
            {
                usleep(1000);
                main_s->dead_philo = 1;
                pthread_mutex_lock(main_s->check_mutex);
                printf("philo %d is dead in : %lu",main_s->philo[i].id, get_time() - main_s->start);
                return (0);
            }
            i++;
        }
    }
    return (1);
}

void    sleep_and_think(t_info *philo)
{
    if (philo->time_ph_ate != philo->main->num_time_eat)
    {
        pthread_mutex_lock(philo->main->check_mutex);
        printf("philo %d is sleeping | time %lu\n",philo->id, get_time() - philo->main->start);
        pthread_mutex_unlock(philo->main->check_mutex);
        wait_for_philo(philo->main->time_sleep);
        pthread_mutex_lock(philo->main->check_mutex);
        printf("philo %d is thinking | time %lu\n",philo->id, get_time() - philo->main->start);
        pthread_mutex_unlock(philo->main->check_mutex);
    }
}
void *life(void *a)
{
    t_info *philo;

    philo = (t_info *)a;
    while (!philo->main->dead_philo && philo->time_ph_ate != philo->main->num_time_eat)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->main->check_mutex);
        printf("philo %d has taken the right fork | time : %lu\n", philo->id, get_time() - philo->main->start);
        pthread_mutex_unlock(philo->main->check_mutex);
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->main->check_mutex);
        printf("philo %d has taken the left fork | time : %lu\n", philo->id, get_time() - philo->main->start);
        pthread_mutex_unlock(philo->main->check_mutex);
        pthread_mutex_lock(philo->main->check_mutex);
        philo->last_eat = get_time();
        printf("philo %d is eating | time : %lu \n",philo->id, get_time() -  philo->main->start);
        pthread_mutex_unlock(philo->main->check_mutex);
        wait_for_philo(philo->main->time_eat);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        sleep_and_think(philo);
        philo->time_ph_ate++;
    }
    return NULL;
}

void create_thread(t_args *main_s)
{
    int i;

    

    i = 0;
    main_s->start = get_time();
    while (i < main_s->num_philos)
    {
        main_s->philo[i].main = main_s;
        i++;
    }
    i = 0;
    while (i < main_s->num_philos)
    {
        pthread_create(&main_s->philo[i].th,NULL, life , &main_s->philo[i]);

        usleep(100);
        i += 2;
    }
    i = 1;
    while (i < main_s->num_philos)
    {
        pthread_create(&main_s->philo[i].th,NULL, life ,  &main_s->philo[i]);
        usleep(100);
        i += 2;
    }
    if (!check(main_s))
        return ;
    i = 0;
    while (i < main_s->num_philos)
    {
        pthread_join(main_s->philo[i].th,NULL);
        i++;
    }
}

