#include "philo.h"

void wait_for_philo(int time)
{
    unsigned long a;

    a = get_time();
    while (get_time() < a + time)
    {
        usleep(50);
    }
}

unsigned long	get_time(void)
{
	struct timeval		tv;
	unsigned long		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);
}