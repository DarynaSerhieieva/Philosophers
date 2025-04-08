#include "philo.h"

time_t	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	start_delay(time_t start_time)
{
	while (current_time_ms() < start_time)
		continue ;
}
