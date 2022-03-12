#include "philo.h"

void parsing(int ac, char **av, t_args *main_s)
{
    main_s->dead_philo = 0;
    main_s->num_philos = ft_atoi(av[1]);
    main_s->time_die = ft_atoi(av[2]);
    main_s->time_eat = ft_atoi(av[3]);
    main_s->time_sleep = ft_atoi(av[4]);
    if (ac == 6)
        main_s->num_time_eat = ft_atoi(av[5]);
}

void init_struct(t_args *main_s)
{
    int i;

    i = 0;
    while (i < main_s->num_philos)
    {
        main_s->philo[i].time_ph_ate = 0;
        i++;
    }
}
int main(int ac, char **av)
{
    t_args main_s;

    if (ac == 5 || ac == 6)
    {
        if (check_args(ac,av))
        {
            parsing(ac, av, &main_s);
            if (!allocate_struct(&main_s))
                return (0);
            init_struct(&main_s);
            create_mutex(&main_s);
            create_thread(&main_s);
            destroy_mutex(main_s);
        }
    }
}

