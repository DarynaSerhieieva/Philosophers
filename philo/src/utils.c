#include "philo.h"

long	ft_atoi(const char *nptr)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (num > (LONG_MAX - (nptr[i] - '0')) / 10)
		{
			printf("Error: Number exceeds the maximum value for a long.\n");
			exit(1);
		}
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (num);
}

void	free_item(void **item)
{
	if (item && *item)
	{
		free(*item);
		*item = NULL;
	}
}

void	free_memory(pthread_mutex_t **forks, t_philo **philos, int **i_phil)
{
	if (forks)
		free_item((void **)forks);
	if (philos)
		free_item((void **)philos);
	if (i_phil)
		free_item((void **)i_phil);
}

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
