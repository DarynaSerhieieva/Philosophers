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
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (num);
}

void	free_memory(t_table *table)
{
	if (table->forks != NULL)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philosophers != NULL)
	{
		free(table->philosophers);
		table->philosophers = NULL;
	}
}

void	cleanup_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->forks != NULL)
	{
		while (i < table->num_philosophers)
		{
			if (pthread_mutex_destroy(&table->forks[i]) != 0)
				printf("Error: Failed to destroy mutex for fork %d\n", i);
			i++;
		}
	}
	if (pthread_mutex_destroy(&table->print_lock) != 0)
		printf("Error: Failed to destroy mutex for print_lock!\n");
	free_memory(table);
}

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
