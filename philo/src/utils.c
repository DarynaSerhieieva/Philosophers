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

void	free_memory(pthread_mutex_t *forks, t_philo *philosophers)
{
	if (forks)
	{
		free(forks);
		forks = NULL;
	}
	if (philosophers)
	{
		free(philosophers);
		philosophers = NULL;
	}
}

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	lock_unclok(t_philo *philo, char *massege)
{
	long	current_time;

	current_time = current_time_ms();
	pthread_mutex_lock(&philo->table->print_lock);
	if (philo->table->should_stop)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (1);
	}
	printf("%ld %d is %s\n", current_time, philo->id, massege);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}
